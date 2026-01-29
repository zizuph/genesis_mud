/*
 * /d/Gondor/minas/npc/hunthor.c
 *
 * Modification Log:
 * 10-8-94, Olorin: Added code for the quest to retrieve the
 *                  Battle Standard of the Witchking (BSW)
 * 28-5-95, Olorin: Added code for the whodunnit
 * 16-6-95, Olorin: Added support for throwing attackers into prison
 * 12-10-95, Olorin: Tried to make Hunthor use 'say to <target>', but
 *                  this has not been implemented for npcs yet.
 *                  Some changes to remove obsolete syntax.
 * 6-20-00, Gwyneth: Fixed bug with whispering with a player who has
 *                   a name also found in the adjectives list.
 * 7-3-01, Alto: Assign password to sixth circle to players
 *                 if Hunthor did not set the bit for BS quest.
 * jul 27, 05, Finwe: added TELL-ADMIN features
 */
#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/minas/npc/arrest_attacker.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"
#include "/d/Gondor/lebennin/thornlin/ox_quest.h"
#include "/d/Gondor/private/gondor_admin.h"

#define WEP1            (WEP_DIR + "lsword")
#define ARM1            (ARM_DIR + "studl")
#define OFFICE		(MINAS_DIR + "rooms/adoffice")
#define OSG_BRIDGE	(ANO_DIR + "osgiliath/wbridge1")

/*
 * Temporary definitions until the 'say to <target>' has been added
 * to the mudlib for npcs, too.
 */
#define NEW_SAY_TO	"say to "+name
#define SAY_TO		"say"

/*
 *	Definitions for the arresting of players
 */
#define PRISON		(MINAS_DIR + "rooms/prison")
#define PARALYZE_ID	"_Minas_Tirith_arrest_paralyze"
#define CHAINS_SUBLOC	"_MT_arrest_chains_subloc"
#define LIVE_O_MT_ARRESTED	"_live_o_MT_arrested"
#define LIVE_I_ASKED_HUNTHOR	"_live_i_asked_hunthor"

// release after 15 minutes
#define PRISON_TIME	900
// parole time is one year in game time
#define PAROLE_TIME	365

#define CLOSED_6TH_CIRCLE     0

/*
 *  Prototypes
 */
static varargs void    do_intro(object tp);
static void    quest_thornlin_inform(object pl);
static void    check_thornlin_quest(object horn, object pl, string str);
static void    quest_gilraen_inform(object pl);
static void    quest_murder_inform(object pl);
static void    check_murder_quest(object pl);
static void    reward_murder_quest(object pl);
static void    quest_bsw_inform(object pl);
static void    check_bsw_quest(object pl, object standard);
static void    pelargir_tour(object tp, object note);
static int     do_ask_for_note(object player);
public int     accept_tour(string str);
public int     query_not_trusted(object pl);
static int     test_reward(object player,object obj);
static string  password_inform(int n);

/*
 *  Global variables
 */
static int     intro_id = 0;
static string *tours = "/d/Gondor/common/quest/tours"->query_tours(),
              *received_key = ({}),
              *solved_murder_quest = ({});

void
create_monster()
{
    set_living_name("hunthor");
    set_title("the Master of Advice");
    set_name("hunthor");
    set_race_name("human");
    set_adj("grey-haired");
    set_adj("tall");
    set_long(BSN("This is Hunthor, the Master of Advice in Minas Tirith. "+
        "He is a friendly fellow, and may quite possibly be able to provide "+
        "you with a task if you ask him."));
    default_config_npc(55 + random(10));
    /* But we want it to have more hitpoints */
    set_base_stat(SS_STR, 70 + random(10));
    set_base_stat(SS_CON, 75 + random(10));
    set_base_stat(SS_INT, 75 + random(10));
    set_base_stat(SS_WIS, 70 + random(15));

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_2H_COMBAT,55);
    set_skill(SS_PARRY,75);
    set_skill(SS_DEFENCE,85);
    set_skill(SS_SNEAK,53);
    set_skill(SS_AWARENESS,55);
    set_alignment(600);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_chat_time(7);
    add_cchat("Alarm!");
    add_cchat("Help! I'm being attacked by a maniac!");
    add_cchat("Ok, come on, bastard! I'll beat you up badly!");
    add_cchat("We won't give in to the enemy, killing me won't help!");
    add_cchat("You won't get away with this!");
    add_cchat("You will regret this when you are lying in chains in the "
      + "prison!");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"help"}), VBFC_ME("ask_help"));
    add_ask(({"tour","task","quest","job"}), VBFC_ME("quest_inform"));
    add_ask(({"about tour","about task","about quest","about job"}),
        VBFC_ME("quest_inform"));
    add_ask(({"for tour","for task","for quest","for job"}),
        VBFC_ME("quest_inform"));
    add_ask(({"about ithilien","ithilien"}), VBFC_ME("ask_ithilien"));
    add_ask(({"about leave","for leave","leave","about permission",
        "for permission","permission"}), VBFC_ME("ask_leave"));
    add_ask(({"about ferry","ferry","about anduin","anduin","about crossing",
        "about crossing the anduin","cross", "bridge", "about bridge", }),
        VBFC_ME("cross_anduin"));
    add_ask(({"osgiliath", }), VBFC_ME("ask_osgiliath"));
    add_ask(({"about rohan","rohan","about edoras","edoras"}),
        VBFC_ME("ask_rohan"));
    add_ask(({"key to sewer", "key to sewers", "sewer", "sewers", "drain",
        "drains", }), VBFC_ME("ask_sewer"));
    add_ask(({"lossarnach", }), VBFC_ME("ask_lossarnach"));
    FIX_EUID
    TELL_ADMIN("Hunthor was cloned at " + ctime(time()));

}

void
arm_me()
{
    FIX_EUID

    command("say Ooops, I forgot to wield my equipment!");
    clone_object(WEP1)->move(TO);
    command("wield longsword");
    clone_object(ARM1)->move(TO);
    command("wear armour");

    do_intro();
}

public void
init_living()
{
    object  tp = TP,
            note;

    ::init_living();

    if (present("Minas_Tirith_Tour_Note",tp))
        set_alarm(0.0, 0.0, &do_ask_for_note(tp));
    if (objectp(note = present("Pelargir_Tour_Note", tp)))
        set_alarm(2.0, 0.0, &pelargir_tour(tp, note));
    if (living(tp) && interactive(tp) && CAN_SEE(TO, tp) &&
        !(tp->query_met(query_real_name())))
        do_intro(tp);

    add_action(accept_tour, "accept");
}

/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public void
catch_question(string question)
{
    int     n;
    object  tp = TP;
    string *arr,
            name = tp->query_real_name(),
            str2,
            str;

    if ((query_friend_or_foe(tp) < 0) && (!tp->query_wiz_level()))
    {
        command(SAY_TO + " We do not want you here in Minas Tirith!");
        command(SAY_TO + " Leave before I call the guards!");
        return;
    }

    question = LOW(question);

    if (question == "password")
    {
        set_alarm(1.0, 0.0, &password_inform(0));
        return;
    }

    if ((sscanf(question, "%s password %s", str, str2) < 1) &&
        (sscanf(question, "%s password", str) < 1) &&
        (sscanf(question, "password %s", str) < 1))
    {
        ::catch_question(question);
        return;
    }

    if (!parse_command(question, ({}),
        "[for] [the] 'password' [to] / [for] [the] %w 'circle' / 'level' / 'gate'",
        str))
    {
        command("peer "+name);
        command(SAY_TO + " Hmm, are you trying to ask me for the password to one of the gates?");
        command(SAY_TO + " If so, then try to 'ask hunthor for the password to the third gate', for example.");
        return;
    }

    if ((n = LANG_ORDW(str)) > 0)
    {
        set_alarm(1.0, 0.0, &password_inform(n));
        return;
    }

    command("hmm");
    command("ponder "+question);
    command(SAY_TO + " Perhaps you should try to ask me, for example, for the password to the third gate?");
    return;
}

void
return_object(object obj, object to)
{
    string  name = to->query_real_name();

    if (obj->id("coin"))
        return;

    command(SAY_TO + " I don't think I need that.");
    to->catch_msg("The Master gives the "+obj->short()+" back to you.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" gives "+LANG_ADDART(obj->short())+
        " to "+QTNAME(to)+".\n", to);
    if (obj->move(to))
       obj->move(to, 1);
}

void
enter_inv(object obj,object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj))
        return;
    if (!living(from))
        return;

    // Is this the key to the sewers that is returned? (Whodunnit)
    if (obj->id(MT_PW5_SEWER_KEY))
        set_alarm(1.0, 0.0, &check_murder_quest(from));
    else if (obj->id("_ithilien_badge"))
        return;
    else if (obj == present("Minas_Tirith_Tour_Note"))
        set_alarm(0.5, 0.0, &test_reward(from, obj));
    else if (obj->id(BSW_BATTLE_STANDARD))
        set_alarm(1.0, 0.0, &check_bsw_quest(from, obj));
    // Thornlin ox quest
    else if (obj->id(THORNLIN_OX_DAMAGED_HORN))
        set_alarm(2.5, 0.0, &check_thornlin_quest(obj, from, "damaged"));
    else if (obj->id(THORNLIN_OX_HORN))
        set_alarm(2.5, 0.0, &check_thornlin_quest(obj, from, "horn"));
    else if (obj->id(THORNLIN_OX_HUNTING_HORN))
        set_alarm(2.5, 0.0, &check_thornlin_quest(obj, from, "hunting"));
    else
        set_alarm(0.5, 0.0, &return_object(obj, from));
}

static varargs void
do_intro(object tp)
{
    if (!objectp(tp))
        tp = TP;

    if (tp->query_npc() || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, tp) || tp->query_met(query_real_name()))
        return;
    if (sizeof(get_alarm(intro_id)))
        return;
    intro_id = set_alarm(3.0, 0.0, &command("introduce myself to "
      + tp->query_name()));
    return;
}

public void
add_introduced(string str)
{
    object  who = find_player(str);

    if (objectp(who))
        do_intro(who);
}

static void
password_inform(int n)
{
    object  tp = TP;
    string  name = tp->query_real_name(),
//           *bsw_solved,
            pw;

    switch (n)
    {
         case 0:
             command(SAY_TO + " Well, which password do you want to know?");
             command("peer "+ name);
             command(SAY_TO + " All gates have different passwords, didn't you know that?");
             break;
        case 1:
        case 2:
        case 3:
             command(SAY_TO + " You do not need any password to be allowed beyond the "
               + CAP(LANG_WORD(n))+" Gate.");
             command("sigh");
             command("say Alas, we might have to change that if the War breaks out!");
             break;
        case 4:
        // Password Quest: Gilraen Wolfcave
            if (tp->test_bit("Gondor", TOUR_GROUP, GILRAEN_WOLFCAVE_BIT))
            {
                   pw = M_TIRITH_PW_MASTER->query_password(n, name);
                   command("whisper " + OB_NAME(TP) + " The password for the "+CAP(LANG_WORD(n))
                     + " Circle " + "is '"+pw+"'.");
            }
            else
            {
               command(SAY_TO + " Before you may enter the fourth circle of the city, you "
                 + "will have to solve a task for a citizen of Minas Tirith!");
               set_alarm(2.0, 0.0, &quest_gilraen_inform(tp));
            }
            break;
        case 5:
        // Password Quest: Minas Tirith Murder Quest
            if (tp->test_bit("Gondor", TOUR_GROUP, MTIRITH_MURDER_BIT))
            {
                   pw = M_TIRITH_PW_MASTER->query_password(n, name);
                   command("whisper "+ OB_NAME(TP) +" The password for the "+CAP(LANG_WORD(n))
                     + " Circle " + "is '"+pw+"'.");
            }
            else
            {
               command(SAY_TO + " Before you may enter the fifth circle of the city, you "
                 + "will have to solve a task for the city of Minas Tirith!");
               set_alarm(2.0, 0.0, &quest_murder_inform(tp));
            }
            break;
        case 6:
        // Password Quest: Battle Standard of Angmar
            if (tp->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT))
            {
                  /* What an incredible hog for a simple message!
                  bsw_solved = OFFICE->query_bsw_solved();
                  if (member_array(name, bsw_solved) < 0)
                  {
                      OFFICE->add_bsw_solved(name);
                      pw = M_TIRITH_PW_MASTER->query_password(6, name);
                      if (strlen(pw))
                      {
                          command("whisper "+ OB_NAME(TP) +" Hmm. You have " +
                              "the look of one who has once served the " +
                              "Enemy. We will be keeping a careful watch on " +
                              "you. The password for the sixth circle is '"+
                              pw+"'.");
                      }
                  }
                  else
                  {
                  */
                        pw = M_TIRITH_PW_MASTER->query_password(n, name);
                        command("whisper "+ OB_NAME(TP) +
                            " The password for the "+CAP(LANG_WORD(n))
                            + " Circle " + "is '"+pw+"'.");
#if CLOSED_6TH_CIRCLE
                            command("whisper "+ OB_NAME(TP) +" But at " +
                                "present, the Gate has to remain closed "
                                + "at all times by order of the Steward.");
#endif
                  //}
            }
            else
            {
                command(SAY_TO + " Before you may enter the "+CAP(LANG_WORD(n))
                  + " Circle of the city, you "
                  + "will have to solve a task for the Steward!");
                set_alarm(2.0, 0.0, &quest_bsw_inform(tp));
            }
            break;
        case 7:
        // Password Quest: RotK, the Minas Tirith Part
            command("oops");
            command(SAY_TO + " I'm afraid I've forgotten that password!");
            command(SAY_TO + " Come back later, please!");
            break;
        default:
            command("gasp");
            command(SAY_TO + " But the city does not have any "+LANG_WORD(n)+" gate!");
            break;
    }
}

string
quest_inform()
{
    int     qno;
    object  tp = TP;
    string  qstr,
            name = tp->query_real_name();

    qno = query_bin_bits(TOUR_GROUP, TOUR_FIRST_BIT, TOUR_NO_OF_BITS, tp);

    if (qno >= sizeof(tours))
    {
        // Thornlin ox quest solved?
        if (!(tp->test_bit("Gondor", THORNLIN_OX_GROUP, THORNLIN_OX_BIT)))
            set_alarm(2.0, 0.0, &quest_thornlin_inform(tp));
        // Gilraen wolfcave quest solved?
        else if (!(tp->test_bit("Gondor", TOUR_GROUP, GILRAEN_WOLFCAVE_BIT)))
            set_alarm(2.0, 0.0, &quest_gilraen_inform(tp));
        // Murder quest solved?
        else if (!(tp->test_bit("Gondor", TOUR_GROUP, MTIRITH_MURDER_BIT)))
            set_alarm(2.0, 0.0, &quest_murder_inform(tp));
        // BSW quest solved?
        else if (!(tp->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT)))
            set_alarm(2.0, 0.0, &quest_bsw_inform(tp));
        else
            command(SAY_TO + " I'm sorry, there are no more tours or quests at the moment.");
        return "";
    }

    command(SAY_TO + " This is what you should do:");
    command("whisper "+ OB_NAME(TP) +" "+BS(tours[qno]));
    command(SAY_TO + " If you want to do this task, type 'accept task'");
    tp->add_prop(LIVE_I_ASKED_HUNTHOR, 1);
    command("smile");
    return "";
}

string
ask_ithilien()
{
    int iranger;
    command("say Ithilien once was the garden of Gondor.");
    command("say It lies east of the Anduin, between the river " );
    command("say and the Ephel Duath, the Mountains of Shadow.");
    command("say Since the armies of the Evil One reign in Ithilien");
    command("say no one may enter cross the Anduin, save by ");
    command("say leave of the Steward.");
    if (IS_RANGER(TP))
    {
        iranger = 1;
        command("say But of course, rangers are not affected by that order!");
        command("say On the contrary, we expect them to go to Ithilien ");
        command("say to assist us in our struggle!");
        command("say If you do not know how to cross the Anduin, ask me.");
        return "";
    }
    command("say I am empowered to grant that leave.");
    command("say If you desire to assist us in our fight, ");
    command("say then ask me for it.");
    return "";
}

string
ask_leave()
{
    int     palign;
    object  badge,
            plbadge;
    string  name = TP->query_real_name();

    if (IS_RANGER(TP))
    {
        command(SAY_TO + " As a ranger, you are free to go to Ithilien "
          + "whenever your other duties allow it!");
    }
    else if (plbadge=present("_ithilien_badge", TP))
    {
        if(TP->query_prop("_no_pass_to_ithilien"))
        {
            command("glare " + name);
            command(SAY_TO + " You have no right to that token any more!");
            TP->catch_msg(QCTNAME(TO) + " takes away your badge.\n");
            plbadge->move(TO);
            say(QCTNAME(TO) + " takes away a badge from " + QCTNAME(TP) + ".\n");
            command("emote breaks the badge.");
            plbadge->remove_object();
            TP->remove_prop("_ithilien_leave_by_hunthor");
            command(SAY_TO + " Leave now before I call the guards!");
        }
        else if (plbadge->query_prop("_ithilien_leave_name") == TP->query_real_name())
        {
            command(SAY_TO + " You already have the Steward's leave!");
            command(SAY_TO + " What more do you want?");
            command("peer " + name);
        }
        else
        {
            command("glare " + name);
            command(SAY_TO + " How did you get that badge?");
            TP->catch_msg(QCTNAME(TO) + " takes away your badge.\n");
            plbadge->move(TO);
            say(QCTNAME(TO) + " takes away a badge from " + QCTNAME(TP) + ".\n");
            command(SAY_TO + " It wasn't yours!");
            command(SAY_TO + " We don't like people running around with a pass "
              + "that Gondor issued to someone else!");
            command(SAY_TO + " Leave now before I call the guards!");
            command("emote breaks the badge.");
            plbadge->remove_object();
            TP->add_prop("_no_pass_to_ithilien",1);
        }
    }
    else if(TP->query_prop("_ithilien_leave_by_hunthor"))
    {
        command("sigh");
        command(SAY_TO + " I already gave you a token showing that you could "
          + "enter Ithilien by leave of the Steward, but you lost that token!");
        command("glare " + name);
        command(SAY_TO + " You disappointed me!");
        command(SAY_TO + " You are herewith forbidden under punishment of "
          + "to enter Ithilien!");
        TP->add_prop("_no_pass_to_ithilien",1);
        TP->remove_prop("_ithilien_leave_by_hunthor");
        command(SAY_TO + " Leave now before I call the guards!");
    }
    else if((palign=TP->query_alignment()) < -250 || TP->query_race() == "goblin")
    {
        command(SAY_TO + " Gondor does not care for those of your kind!");
        command("glare " + name);
        command(SAY_TO + " Leave before I call the guards!");
    }
    else if(palign < 0 || TP->query_prop("_no_pass_to_ithilien"))
    {
        command(SAY_TO + " Gondor does not trust you!");
        command(SAY_TO + " We suffer your presence here, "
          + "but do not try to take advantage of our generosity!");
        command(SAY_TO + " Leave now!");
    }
    else if(palign < 100)
    {
        command("hmm");
        command(SAY_TO + " I am not sure that I can trust your loyalty.");
        command(SAY_TO + " I will not grant you leave to go to Ithilien!");
        command(SAY_TO + " Do not go there, or you will be punished!");
    }
    else
    {
        badge = clone_object(OBJ_DIR + "ithilien_badge");
        badge->move(TO, 1);
        if(!badge)
        {
            command(SAY_TO + " Right now, we don't need your help!");
            return "";
        }
        command("peer " + TP->query_real_name());
        command(SAY_TO + " We can use all the help that is offered to us!");
        command("thank " + TP->query_real_name());
        command(SAY_TO + " But I warn you!");
        command(SAY_TO + " There are great dangers in Ithilien!");
        command(SAY_TO + " Especially for those that try to betray Gondor!");
        command(SAY_TO + " So take great care to prove yourself worthy of my trust.");
        badge->add_prop("_ithilien_leave_name",TP->query_real_name());
        command("give " + badge->query_name() + " to " + name);
        if (present(badge, TO))
        {
            command(SAY_TO + " You are carrying too much.");
            command(SAY_TO + " I cannot give the badge to you that would "
             + "proof that you are in Ithilien by leave of the Steward!");
            command(SAY_TO + " Ask me again when you are less overloaded!");
            badge->remove_object();
            return "";
        }
        TP->add_prop("_ithilien_leave_by_hunthor",1);
        command(SAY_TO + " This badge will be proof that you are in Ithilien by leave of the Steward!");
        command(SAY_TO + " Do not lose it, do not give it away!");
        command(SAY_TO + " And under no circumstances should you let it fall into the hands of the enemy!");
        command(SAY_TO + " If you do not know how to cross the Anduin, ask me!");
    }
    return "";
}

string
cross_anduin()
{
    object  badge;
    int     i_answer = 0;

    if(IS_RANGER(TP))
        i_answer = 1;
    else if (objectp(badge = present("_ithilien_badge", TP)))
    {
        if (TP->query_prop("_no_pass_to_ithilien"))
            i_answer = 0;
        else if (badge->query_prop("_ithilien_leave_name") == TP->query_real_name())
            i_answer = 1;
    }
    command("say The Anduin is the mightiest river in Middle Earth.");
    command("say It divides Gondor into two parts, Ithilien on the "
      + "eastern bank, and Anorien and the coastlands to the west of it.");

    if (OSG_BRIDGE->query_bridge_broken())
    {
        command("say There was a bridge crossing the Anduin in Osgiliath, "
          + "the former capital of Gondor.");
        command("say But when the armies of the Dark Lord defeated our last "
          + "troops in Ithilien, our rearguard had to destroy the bridge "
          + "to prevent the enemy from crossing the Anduin on it.");
        if (i_answer)
        {
            command("say But the rangers still run a ferry that crosses "
              + "the river at night.");
            command("say Go to Osgiliath!");
            command("say You will find the ferry under the ruins of the bridge.");
            command("say Farewell friend!");
            command("wave " + TP->query_real_name());
        }
    }

    command("say The only bridge that crosses the Anduin between the Falls "
      + "of Rauros in the north and the sea is in Osgiliath.");
    if (!i_answer)
    {
        command("say But only those who have the Leave of the Steward may "
          + "enter Ithilien.");
    }
    return "";
}
 
public string
ask_osgiliath()
{
    command("say Osgiliath once was the capital of Gondor.");
    command("say But it has fallen into ruins long ago.");
    if (OSG_BRIDGE->query_bridge_broken())
    {
        command("say We had a small force holding a bridge head on the eastern "
          + "bank of the Anduin.");
        command("say But in the last attack that came out of Mordor "
          + "our troops were driven back over the bridge, and they just "
          + "barely managed to destroy it, to prevent the enemy from "
          + "using it.");
    }
    else
    {
        command("say We still hold the city, and we even have a small "
          + "force holding a bridge head on the east bank of the Anduin.");
        command("say The bridge in Osgiliath is the only that crosses "
          + "the Anduin between the Falls of Rauros and the sea.");
    }
    return "";
}

int     query_knight_prestige() { return -10; }

string
ask_rohan()
{
    command("say Edoras is the capital of Rohan, the land of the Rohirrim.");
    command("say Since the times of Eorl the Young there has been ");
    command("say friendship between Gondor and Rohan!");
    command("say Rohan lies north of the Ered Nimrais, the White Mountains.");
    command("say From Minas Tirith, follow the road northward through Anorien.");
    command("say You will come to Firien Forest and the Mering Stream.");
    command("say That is the border between Gondor and Rohan.");
    return "";
}

string
default_answer()
{
    string  name = TP->query_real_name();

    command(SAY_TO + " I do not know what you are talking about!");
    return "";
}

string
ask_help()
{
    string  name = TP->query_real_name();

    command(SAY_TO + " Help? You want help with what?");
    if (TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command(SAY_TO + " Did you find any hints about the murder?");   
        command(SAY_TO + " What kind of help do you need?");
    }
    else
    {
        command(SAY_TO + " Perhaps you are looking for a job?");
    }
    command("peer "+name);
    return "";
}

/*
 * Functions for the tours
 */
static int
do_ask_for_note(object player)
{
    string  name = player->query_real_name();

    command(SAY_TO + " Hello again! How did your tour go? Give me the note, please.");
    command("smile "+name);
    return 1;
}

public int
accept_tour(string str)
{
    int     qno;
    object  note,
            tp = TP;
    string  name = tp->query_real_name();

    if (!str)
    {
        NFN("Accept what?");
        return 0;
    }

    if (str == "task")
    {
        if (!(tp->query_prop(LIVE_I_ASKED_HUNTHOR)))
        {
            command("peer "+name);
            command(SAY_TO + " But I didn't give you any task yet!");
            return 1;
        }

        tp->remove_prop(LIVE_I_ASKED_HUNTHOR);
        say(QCTNAME(tp)+" asks the Master Advisor for a task.\n",tp);
        qno = query_bin_bits(TOUR_GROUP, TOUR_FIRST_BIT, TOUR_NO_OF_BITS,tp);
        if (qno >= sizeof(tours)) {
            command(SAY_TO + " Sorry, I have no more tasks for you, "
              + tp->query_race_name()+".");
            return 1;
        }

        command(SAY_TO + " Good! Here is a note that will show that "
          + "you are a tourist.");
        command(SAY_TO + " When you have found the place, come back to me.");
        note = clone_object("/d/Gondor/elessar/quest/tournote");
        note->set_tour_no(qno);
        if ((note->move(tp)))
        {
            command(SAY_TO + " Hmm. You couldn't carry more. "
                  + "Well, I'll drop it here.");
            note->move(environment(TO));
        }
        return 1;
    }
    return 0;
}

void
dest_note(object note)
{
    note->remove_object();
}

int
do_reward(object player, int qno)
{
    int     reward;
    string  name = player->query_real_name();

    reward = 0;
    set_bin_bits(TOUR_GROUP, TOUR_FIRST_BIT, TOUR_NO_OF_BITS,player,qno);
    command(SAY_TO + " Congratulations! You have fulfilled the task I gave you!");
    command("shake "+name);
    if (qno < 4)
        reward = 50;
    else if (qno == 4)
        reward = 100;
    player->add_exp_quest(reward);
    log_file("mini", CAP(name)+" did miniquest "
      + qno+" and got "+reward+" xp. " + ctime(time())+".\n", 0);
    tell_object(player,"You feel a little more experienced.\n");
    return 1;
}

static int
test_reward(object player,object obj)
{
    string  name = player->query_real_name();

    if (obj->query_tour_no() == 
        query_bin_bits(TOUR_GROUP, TOUR_FIRST_BIT, TOUR_NO_OF_BITS, player))
    {
        if (obj->query_tour_done())
        {
            do_reward(player,obj->query_tour_no()+1);
            set_alarm(5.0, 0.0, &dest_note(obj));
            return 1;
        }
        else
        {
            command(SAY_TO + " But you haven't finished the task?");
            command(SAY_TO + " Oh well - if you decide to try again, "
                  + "you're welcome to ask.");
            obj->remove_object();
            return 1;
        }
    }
    command(SAY_TO + " You were not supposed to do that one - "
          + "have you been cheating?");
    command("glare "+name);
    set_alarm(5.0, 0.0, &dest_note(obj));
    return 1;
}

/*
 *	The tour from Pelargir
 */
void
advertise(object tp)
{
    string  name = tp->query_real_name();

    if (!objectp(tp) || !present(tp, ENV(TO)))
         return;

    command(SAY_TO + " If you are looking for more jobs, you can also ask me.");
    command("smile " + name);
}

static void
pelargir_tour(object tp, object note)
{
    int     qno;
    string  name = tp->query_real_name();

    if (!objectp(tp) || !present(tp, ENV(TO)))
        return;

    if ((note->query_tour_no() != 3) || (note->query_tour_done()))
        return;

    command("greet " + name);
    command(SAY_TO + " Ah, you are coming from Carastur!");
    command("smile " + name);
    command("emote takes the tour note.");
    if (note->query_player_name() != name)
    {
        command("emote studies the tour note.");
        command(SAY_TO + " But this isn't your note!");
        command("glare "+name);
        command(SAY_TO + " You have been bribed to do this "
          + "tour for someone, haven't you?");
        command("emote rips the tour note in little pieces.");
        command(SAY_TO + " Get out of my sight. You disappoint me!");
        command("sigh");
        log_file("mini", tp->query_cap_name()+" tried to cheat on "
          + "a Pelargir tour for "+CAP(note->query_player_name())
          + ". " + ctime(time())+".\n", 0);
        note->remove_object();
        return;
    }
    command("emote writes a few sentences on the tour note.");
    command("emote gives the tour note back.");

    note->set_tour_done();

    command(SAY_TO + " Please return to Pelargir now and give the note back to Carastur.");
    command(SAY_TO + " Your task is done.");

    if (query_bin_bits(TOUR_GROUP, TOUR_FIRST_BIT, TOUR_NO_OF_BITS, tp)
        < sizeof(tours))
        set_alarm(3.0, 0.0, &advertise(tp));
}

/*
 * Functions for Thornlin Ox Quest
 */
string
ask_lossarnach()
{
    command("say Lossarnach is an area in Gondor.");
    command("say It comprises the mountain-valleys just southwest of Minas Tirith.");
    command("say You can reach it from the road running from the Harlond to Pelargir.");
    return "";
}

static void
quest_thornlin_inform(object pl)
{
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
        return;

    if (pl->query_prop(THORNLIN_I_SENT_TO_THORNLIN))
    {
        command(SAY_TO + " I already sent you to Lossarnach, didn't I?");
        command(SAY_TO + " Go there and try to get find an araw horn!");
        return;
    }
    command(SAY_TO + " The Steward is looking for a hunting horn made from the horn of an araw ox.");
    command(SAY_TO + " There are some farmers in Lossarnach who breed cattle.");
    command(SAY_TO + " Some might have araw oxen.");
    command(SAY_TO + " Go there and see if you can get an araw horn!");
    START_QUEST(pl, "THORNLIN OX QUEST");
}

void
reward_thornlin_quest(object horn, object pl)
{
    int     exp;
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
        return;

    // did the player take a short cut?
    if (!pl->query_prop(THORNLIN_I_SOLVED_OX_QUEST))
    {
        command(SAY_TO + " But where did you get it?");
        command(SAY_TO + " I received reports from a village in "
          + "Lossarnach that someone stole an araw ox!");
        command(SAY_TO + " I hope that wasn't you!");
        command(SAY_TO + " But I'm afraid that I cannot give you your "
          + "reward if there is doubt if you came legally into possession of "
          + "this horn!");
        return;
    }

    command(SAY_TO + " The steward will be pleased!");
    MONEY_MAKE_GC(2)->move(TO);
    command("give gold coins to "+name);

    if (pl->test_bit("Gondor", THORNLIN_OX_GROUP, THORNLIN_OX_BIT))
        return;

    if ((exp = pl->query_exp()) > THORNLIN_OX_EXP)
        exp = THORNLIN_OX_EXP;
    pl->add_exp_quest(exp);
    pl->adjust_alignment(50);
    pl->set_bit(THORNLIN_OX_GROUP, THORNLIN_OX_BIT);
    pl->catch_msg("You feel more experienced!\n");
    LOG_QUEST(pl, exp, "THORNLIN OX QUEST");
    pl->remove_prop(THORNLIN_I_SOLVED_OX_QUEST);
    pl->remove_prop(I_KILLED_OX);

    horn->remove_object();
}

static void
check_thornlin_quest(object horn, object pl, string str)
{
    string  name = pl->query_real_name();

    switch (str)
    {
        case "damaged":
            command(SAY_TO + " But the horn is damaged!");
            command(SAY_TO + " We cannot do anything with a damaged horn!");
            set_alarm(2.0, 0.0, &return_object(horn, pl));
            break;
        case "horn":
            command("hmm");
            command("emote inspects the "+horn->short()+" carefully.");
            command(SAY_TO + " Yes, that's the horn of an araw ox!");
            command(SAY_TO + " But it is not a hunting horn.");
            command("ponder");
            command(SAY_TO + " You should try to find a carpenter who "
              + "could make a hunting horn out of this horn.");
            set_alarm(2.0, 0.0, &return_object(horn, pl));
            break;
        case "hunting":
            command("smile "+name);
            command(SAY_TO + " Wonderful! A hunting horn made from the horn of an araw ox!");
            command("blow horn");
            set_alarm(2.0, 0.0, &reward_thornlin_quest(horn, pl));
            break;
    }
}

/*
 * Functions for the Wolfcave Quest
 * Password quest to the fourth circle
 */
static void
quest_gilraen_inform(object pl)
{
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
        return;

    if (pl->query_prop("_Gondor_i_sent_to_Gilraen"))
    {
        command(SAY_TO + " I already sent you to the Lady Gilraen, didn't I?");
        command(SAY_TO + " Go and talk to her!");
        return;
    }
    command(SAY_TO + " Hmm, you are looking for a task?");
    command(SAY_TO + " The Lady Gilraen is looking for someone to help her.");
    command(SAY_TO + " You can find her in the second circle.");
    pl->add_prop("_Gondor_i_sent_to_Gilraen", 1);
}

/*
 * Functions for the Minas Tirith Murder Quest (Whodunit)
 * Password quest to the fifth circle
 */
static void
quest_murder_inform(object pl)
{
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
        return;

/* Commented out due to unsolvable bug in prison querying.
    if (query_not_trusted(pl))
    {
        command("peer "+name);
        command(SAY_TO + " I do not think that you are the right person to investigate a murder!");
        command(SAY_TO + " Come back later.");
        command(SAY_TO + " I might have changed my mind in a few weeks, but right now I don't trust you.");
        return;
    }
*/

    if (pl->query_prop(MT_PW5_I_HUNTHOR_SENT_ME))
    {
        command(SAY_TO + " I already sent you to go and find out "
          + "who killed Gimilzor, didn't I?");
        command(SAY_TO + " Go, find the murderer, and bring him to me!");
        return;
    }

    pl->add_prop(MT_PW5_I_HUNTHOR_SENT_ME, 1);

    MT_PW5_MASTER->load_me();
    MT_PW5_MASTER->set_murderer(pl);

    command("hmm");
    command(SAY_TO + " There has been a murder in the city.");
    command(SAY_TO + " Someone has treacherously murdered Gimilzor.");
    command(SAY_TO + " He was a very respected citizen of an ancient family of the Dunedain.");
    command(SAY_TO + " His murderer stabbed him to death in his own house.");
    command("sigh");
    command(SAY_TO + " I want you to find out who the murderer is and to bring him to me.");
    command(SAY_TO + " And I want the murderer alive!");
    command(SAY_TO + " You can find Gimilzor's house in the fourth circle.");
    command(SAY_TO + " If you need help later, after you have found out more, "
      + "you can come back to me.");
    START_QUEST(pl, "MINAS TIRITH WHODUNIT");
}

int
check_sewer_key(object pl)
{
    string  name = pl->query_real_name();

    if (pl->query_prop(MT_PW5_O_SEWER_KEY) || 
        present(MT_PW5_SEWER_KEY, pl) ||
        (member_array(name, received_key) > -1))
    {
        command(SAY_TO + " Could you please return the key to the "
          + "sewers that I have given you, "+CAP(name)+"?");
        return 1;
    }
    return 0;
}

static void
check_murder_quest(object pl)
{
    string  name = pl->query_real_name();

    command(SAY_TO + " Ahh! The key to the sewers!");
    command(SAY_TO + " Thank you for returning it!");
    pl->remove_prop(MT_PW5_O_SEWER_KEY);
    received_key -= ({ name });

    if (member_array(name, solved_murder_quest) > -1)
        set_alarm(2.0, 0.0, &reward_murder_quest(pl));
}

static void
reward_murder_quest(object pl)
{
    int     exp;
    string  name = pl->query_real_name(),
            pw;

    if (!present(pl, ENV(TO)))
        return;

    if (check_sewer_key(pl))
    {
        solved_murder_quest += ({ name });
        return;
    }

    command("thank "+name);
    command(SAY_TO + " I am very grateful that you helped us in this "
      + "matter, "+CAP(name)+"!");
    command("shake "+name);

    if (!pl->test_bit("Gondor", TOUR_GROUP, MTIRITH_MURDER_BIT))
    {
    	FIX_EUID
    	if ((exp = pl->query_exp()) > MTIRITH_MURDER_EXP)
        	exp = MTIRITH_MURDER_EXP;
    	pl->add_exp_quest(exp);
    	pl->adjust_alignment(400);
    	pl->set_bit(MTIRITH_MURDER_GROUP, MTIRITH_MURDER_BIT);
    	pl->catch_msg("You feel more experienced!\n");
    	LOG_QUEST(pl, exp, "MINAS TIRITH WHODUNIT");
    }
    pl->remove_prop(MT_PW5_I_HUNTHOR_SENT_ME);
    pl->remove_prop(MT_PW5_I_SEEN_BLOOD);
    pl->remove_prop(MT_PW5_I_FOUND_MOTIVE);
    pl->remove_prop(MT_PW5_I_FOUND_WEAPON);
    pl->remove_prop(MT_PW5_I_MERDOL_TESTIMONY);
    pw = M_TIRITH_PW_MASTER->query_password(5, name);
    if (strlen(pw))
        command("whisper "+ OB_NAME(TP) +" The password for the fifth circle "
          + "is '"+pw+"'.");
}

void
remove_murderer(object murderer)
{
    string  name = murderer->query_real_name();

    command(SAY_TO + " The Steward will judge your crime and decide which punishment is fit!");
    command(SAY_TO + " You will await the decision of the Steward in prison!");

    murderer->remove_murderer();
}

void
confession_murder_quest(object pl, object murderer)
{
    string  name = murderer->query_real_name();

    if (!present(pl, ENV(TO)))
        return;

    command("glare "+name);
    command(SAY_TO + " Shame on you, "+CAP(name)+"!");
    command(SAY_TO + " To kill your fellow citizens is as low as you can sink.");

    set_alarm(2.0, 0.0, &remove_murderer(murderer));
    set_alarm(4.0, 0.0, &reward_murder_quest(pl));
}

void
give_sewer_key(object tp)
{
    object  key = clone_object(MINAS_DIR + "doors/sewer-c4-key");
    string  name = tp->query_real_name();

    key->add_name(MT_PW5_SEWER_KEY);
    key->move(TO);
    command("give key to "+name);
    command(SAY_TO + " This is the key to the gate that leads down to "
      + "the sewers in the tunnel of the Fourth Circle.");
    tp->add_prop(MT_PW5_O_SEWER_KEY, key);
    command(SAY_TO + " Take good care of that key and do not forget to "
      + "bring it back to me!");
    received_key += ({ name });
}

string
ask_sewer()
{
    string  name = TP->query_real_name();

    command(SAY_TO + " The sewers?");
    command("peer "+name);
    if (TP->query_prop(MT_PW5_O_SEWER_KEY) ||
        (member_array(name, received_key) > -1))
    {
        command(SAY_TO + " But I already gave you the key for the sewers!");
        command(SAY_TO + " What more do you want?");
    }
    else if (TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command(SAY_TO + " Do you think you might find something in the sewers?");
        command("ponder");
        set_alarm(2.0, 0.0, &give_sewer_key(TP));
    }
    else
    {
        command(SAY_TO + " Well, they are under the city and full of rats.");
        command(SAY_TO + " What about them?");
    }
    
    return "";
}

varargs mixed
query_received_key(string name)
{
    if (!strlen(name))
        return received_key;

    return (member_array(LOW(name), received_key));
}

/*
 * Functions for the Quest to retrieve the Battle Standard of the Witchking
 * Password quest to the sixth circle
 */
static void
quest_bsw_inform(object pl)
{
    string  name = pl->query_real_name();

    if (!present(pl, ENV(TO)))
        return;

    if (pl->query_prop(BSW_I_SENT_TO_GALDOR))
    {
        command(SAY_TO + " I already sent you to Galdor, didn't I?");
        command(SAY_TO + " Go and ask him!");
        return;
    }
    command(SAY_TO + " There is a difficult and dangerous task for which the "
          + "Steward for long years has searched someone to solve it!");
    command(SAY_TO + " Go to Galdor, Captain of the Guard. He can tell you more.");
    command(SAY_TO + " You can find him somewhere in the first circle.");
    pl->add_prop(BSW_I_SENT_TO_GALDOR, 1);
    START_QUEST(pl, "BATTLE STANDARD - HUNTHOR");
}

void
reward_repeat(object pl)
{
    string  name = pl->query_real_name();

    command(SAY_TO + " Where did you get this standard?");
    command("glare "+name);
    command(SAY_TO + " Leave before I call the guards!");
    command(SAY_TO + " This standard is part of the heirlooms of the "
          + "House of Hurin, and the Steward doesn't like it when people are "
          + "stealing from him!");
}

void
reward_bsw_quest(object pl)
{
    int     exp;
    string  name = pl->query_real_name(),
            pw;

    if (!present(pl, ENV(TO)))
        return;

    command("examine standard");
    command(SAY_TO + " This is actually the battle standard which "
          + "Earnur captured in the Battle of Fornost from the Witchking!");
    command(SAY_TO + " Well done!");
    command(SAY_TO + " The Steward will be most grateful!");
    FIX_EUID
    if ((exp = pl->query_exp()) > ANGMAR_STANDARD_QUEST_EXP)
        exp = ANGMAR_STANDARD_QUEST_EXP;
    pl->add_exp_quest(exp);
    pl->adjust_alignment(500);
    pl->set_bit(MORGUL_GROUP, ANGMAR_STANDARD_BIT);
    pl->catch_msg("You feel more experienced!\n");
    LOG_QUEST(pl, exp, "BATTLE STANDARD - HUNTHOR");
    pl->remove_prop(BSW_I_FOUND_IT);
    BSW_TREASURY_FILE->remove_enter(name);
//    OFFICE->add_bsw_solved(name);
    pw = M_TIRITH_PW_MASTER->query_password(6, name);
    if (strlen(pw))
    {
        command("whisper "+ OB_NAME(TP) +" The password for the sixth circle "
          + "is '"+pw+"'.");
#if CLOSED_6TH_CIRCLE
       command("whisper "+ OB_NAME(TP) +" But at present, the Gate has to remain closed "
         + "at all times by order of the Steward.");
#endif
    }
}

void
remove_standard(object standard)
{
    standard->remove_object();
}

static void
check_bsw_quest(object pl, object standard)
{
    string  winner,
            name = pl->query_real_name();

    set_alarm(60.0, 0.0, &remove_standard(standard));
    if (pl->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT))
    {
        reward_repeat(pl);
        return;
    }
    if ((winner = standard->query_prop(BSW_S_RETRIEVED_BY)) != name)
    {
        command(SAY_TO + " I have received reports that you have " +
            "stolen this standard from "+CAP(winner)+"!");
        command(SAY_TO + " I do not like people who try to cheat me!");
        command("growl");
        command("shout So be gone before I smash call the guards!");
        return;
    }
    command("hmm");
    set_alarm(1.0, 0.0, &reward_bsw_quest(pl));
}

/*
 *	Functions to throw an offender into prison
 */
void
due_process(object offender)
{
    string  name = offender->query_real_name();

    if (!objectp(offender) || !present(offender, ENV(TO)))
        return;

    command("glare "+name);
    command(SAY_TO + " So you attacked one of our people living here in the City?");
    command(SAY_TO + " Count yourself lucky that the cityguard stopped you before you killed anyone.");

    if (offender->query_prop(MT_PW5_I_HUNTHOR_SENT_ME))
    {
        command(SAY_TO + " I have asked you to find a murderer, not to attack innocent citizens!");
        command(SAY_TO + " What a disappointment that I've been deceived by my trust in you!");
        offender->remove_prop(MT_PW5_I_HUNTHOR_SENT_ME);
    }

    command(SAY_TO + " Unless the Steward decides that your life is "
      + "forfeit, you will pay for that attack in the city jail.");

    command(SAY_TO + " Put this miserable creature into the jail!");

    offender->move_living("into prison", PRISON);
    PRISON->jail_time(offender, PRISON_TIME, "attacked a citizen");
    offender->remove_stun();
    present(PARALYZE_ID, offender)->remove_object();
    offender->remove_prop(LIVE_O_MT_ARRESTED);
    offender->remove_subloc(CHAINS_SUBLOC);
}

public int
query_not_trusted(object pl)
{
    int     ptime,
            today = CLOCK->query_third_age_days();

    PRISON->load_me();
    // the day the player was arrested
    ptime = PRISON->query_prison_day(pl->query_real_name());

    // sanity check, perhaps the prison did not reset?
    if (ptime > today)
    {
        PRISON->remove_prisoner(pl->query_real_name());
        return 0;
    }

    if ((today - ptime) < PAROLE_TIME)
        return 1;

    return 0;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    TELL_ADMIN("[Hunthor attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()) + "]");

    set_alarm(4.0, 0.0, &check_for_guards(ob));
    set_alarm(10.0 + (20.0 * rnd()), 0.0, &arrest_attacker(ob));
}


/* This file is /d/Gondor/morgul/npc/yrchor.c
 *
 * This Captain in the army of Morgul gives out info
 * 	on the standard of Angmar quest
 *
 * Olorin, July 1994
 *
 * Revision History:
 *
 * Revised to accept the Corsair Captain's report for small quest.
 * Talisan,  February 1996
 * Fixed capitalization typo in reward emotes, Serif, May 2002.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_uruk";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"
#include "/d/Gondor/bits.h"

//    Prototypes:
void  do_bit_test(object pl);
void  do_thank(object pl);
void  do_reward(object pl);
void  do_add_exp(object pl);
string long_desc();

//    Global Variables:
int     st_c = 0,
        st_alarm;

object  pl;

public void
create_ithil_uruk()
{
    int     rnd = random(41);

    set_short(0);
    set_pshort("uruk captains");
    set_name("yrchor");
    set_title("the Red, Captain of Morgul");
    add_name("captain");
    add_adj("uruk");
    remove_adj("black-skinned");
    set_long(long_desc);
    
    default_config_npc( 120 + rnd);
    set_base_stat(SS_INT, 130 + rnd);
    set_base_stat(SS_WIS, 130 + rnd);
    set_base_stat(SS_DIS, 145 + rnd);

    set_alignment(-450-rnd*10);
    set_skill(SS_WEP_SWORD,   95);
    set_skill(SS_WEP_POLEARM, 95);
    set_skill(SS_WEP_CLUB,    95);
    set_skill(SS_WEP_AXE,     95);
    set_skill(SS_WEP_KNIFE,   95);
    set_skill(SS_PARRY,       95);
    set_skill(SS_DEFENCE,     95);
    add_prop(CONT_I_HEIGHT, 180+rnd);
    add_prop(CONT_I_WEIGHT, 85000+rnd*500);
    add_prop(CONT_I_VOLUME, 80000+rnd*500);    
    add_prop(LIVE_I_SEE_DARK, 4);

    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"quest", "task", "job", "about quest", "about task",
              "about job", "for quest", "for task", "for job"}), 
              VBFC_ME("ask_quest"));
    add_ask(({"standard", "battle standard", "about standard", 
              "about battle standard"}), VBFC_ME("ask_standard"));
    add_ask(({"angmar", "about angmar"}), VBFC_ME("ask_angmar"));

    add_ask(({"report", "corsairs", "reports", "pirates"}),
        VBFC_ME("ask_report"));
}

string
long_desc()
{
    string  desc = "A large orc, one of the uruk-hai, with crooked " +
                   "legs and long arms that hang almost to the ground, " +
                   "much stronger and meaner than other orcs of " +
                   "lesser breeds. He is captain in the army " +
                   "of Morgul, probably because he is a little more " +
                   "intelligent than others of his race. ";

    if ((TP->query_prop(BSW_I_SENT_TO_YRCHOR)) && (TP->query_met(TO)))
        desc += "This is the captain of Morgul that the Warden of " +
            "the Tower told you to ask about the battle standard " +
            "of the Witchking. ";

    return BSN(desc);
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())) ||
        pl->query_met(query_name()))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

public void
add_introduced(string str)
{
    object  pl = find_player(str);

    if (!objectp(pl) || objectp(query_attack()))
        return;

    check_attack(pl);

    set_alarm(3.0, 0.0, &return_introduce(pl));
}

void
react_default_answer(object pl)
{
    if (objectp(query_attack()))
        return;

    command("say Whaddya want?");
    command("say I dunno whaddya talking of!");
    command("spit");
    command("say Get outta here before I kick ya out.");
}

string
default_answer()
{
    check_attack(TP);
    set_alarm(2.0, 0.0, &react_default_answer(TP));
    return "";
}

void
react_standard_twice(object pl)
{
    command("glare "+pl->query_real_name());
    command("say I told you already everything I know!");
    command("say Now get outta here!");
    command("snarl "+pl->query_real_name());
}

void
react_standard(object pl)
{
    object  scroll;

    if ( (objectp(query_attack())) || (!present(pl, ENV(TO))) )
    {
        st_c = 0;
        remove_alarm(st_alarm);
        return;
    }

    switch(st_c++)
    {
        case 0:
            command("sigh");
            break;
        case 1:
            command("say The battle standard? The one of the Witchking?");
            break;
        case 2:
            command("think");
            command("peer "+pl->query_real_name());
            command("say You are coming from the Warden of the " +
                    "Tower, aren't you?");
            break;
        case 3:
            command("say It's a long story.");
            break;
        case 5:
            command("say But I will make it short!");
            break;
        case 6:
            command("say All we know is that Earnur gave the standard " +
                    "to Mardil, his steward, before he left Minas " +
                    "Tirith to fight our Lord.");
            break;
        case 8:
            command("cackle");
            command("say That much did he reveal under torture.");
            break;
        case 10:
            command("say So the standard went into the treasure of " +
                    "House of Hurin. It was brought to Emyn Arnen " +
                    "before Mardil's death, but that's all we know.");
            break;
        case 11:
            command("say That is, all except for a scroll that I found " +
                    "in Emyn Arnen after we had occupied it.");
            break;
        case 12:
            command("emote starts to search around in the heap of " +
                    "garbage on the floor.");
            break;
        case 16:
            command("emote pulls a scroll out of the pile of " +
                    "rubble.");
            command("say Here it is!");
            break;
        case 18:
            command("shrug");
            command("say Well, if you can make more out of it than I ...");
            break;
        case 19:
            scroll = clone_object(MORGUL_DIR + "quest/bsw/scroll");
            scroll->add_prop(BSW_S_SCROLL_OWNER, pl->query_real_name());
            if (scroll->move(TO))
                scroll->move(TO, 1);
            command("give scroll to "+pl->query_real_name());
            break;
        case 21:
            command("say If you ask me, I'd say that battle standard is " +
                    "rotting away in some dark hole where the tarks hid " +
                    "their precious treasures.");
            break;
        case 22:
            st_c = 0;
            remove_alarm(st_alarm);
        default:
            break;
    }
}

string
ask_angmar()
{
    object  scroll;

    check_attack(TP);

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if (scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
        {
            set_alarm(2.0, 0.0, &react_standard_twice(TP));
            return "";
        }
    }

    if (TP->query_prop(BSW_I_SENT_TO_YRCHOR))
    {
        command("say Don't mention that name!");
        command("say He doesn't want to be called by that name!");
        command("say What do you want to know about Him?");
        return "";
    }
    command("snarl "+TP->query_real_name());
    command("emote whispers: Don't mention that name!");
    set_alarm(1.0, 0.0, &react_default_answer(TP));
    return "";
}

string
ask_quest()
{
    object  scroll;

    check_attack(TP);

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if (scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
        {
            set_alarm(2.0, 0.0, &react_standard_twice(TP));
            return "";
        }
    }

    if (TP->query_prop(BSW_I_SENT_TO_YRCHOR))
    {
        command("peer "+TP->query_real_name());
        command("say You want a task?");
        command("say What kind of task are you thinking of?");
        return "";
    }
    command("snarl "+TP->query_real_name());
    command("say I've no use for you!");
    command("say I'm not offering jobs!");
    command("kick "+TP->query_real_name());
    command("say Now get outta here before I'll have you for breakfast!");
    command("cackle");
    return "";
}

public string
query_nonmet_name()
{
    return "uruk captain";
}

string
ask_standard()
{
    object  scroll;

    check_attack(TP);

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if (scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
        {
            set_alarm(2.0, 0.0, &react_standard_twice(TP));
            return "";
        }
    }

    if (TP->query_prop(BSW_I_SENT_TO_YRCHOR))
    {
        st_c = 0;
        st_alarm = set_alarm(2.0, 1.5, &react_standard(TP));

        return "";
    }
    set_alarm(2.0, 0.0, &react_default_answer(TP));
    return "";
}

string
ask_report()
{
    command("say What...?");
    command("think about the question.");
    command("say Yes, the Captain of the Black Drake corsairs sends me "
      + "reports once in awhile.");
    command("say That is if he comes across something interesting.");
    command("say If you have something from him, give it to me, "
      + "otherwise get out of here!");
    return "";
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
      return;

    if (obj->id("corsair_quest_report"))
      do_bit_test(from);

    else
      {
      command("say I have no need of this, stop wasting my time!");
      obj->remove_object();
      return;
      }
}


/*
 *Function Name:  do_bit_test(object pl)
 *Description:    Sees if the player has already done the quest.
 *Arguments:      pl = player
 */

void
do_bit_test(object pl)
{
    if (pl->test_bit("Gondor", MORGUL_GROUP, POROS_CORSAIRS_BIT))
    do_thank(pl);

    else do_reward(pl);
}


/*
 *Function Name:  do_thank(object pl)
 *Description:    Gives the player a polite response if he has already
 *                done this quest.
 *Arguments:      pl = player
 */

int
do_thank(object pl)
{
    string hname;
    hname = pl->query_real_name();

    if (environment(pl)!=environment(TO))
    return 0;

    set_act_time(1);
    pl->remove_prop("_gondor_i_corsair_quest");

    command("say This is an old report, don't waste my time!");
    command("sneer");
    return 1;
}


/*
 *Function Name:  do_reward()
 *Description:    Sets up the reward sequence if the player has finished
 *                the corsair report quest.
 *Arguments:      pl = player
 */

int
do_reward(object pl)
{
    string hname;
    hname = pl->query_real_name();

    if (!present(pl,environment(TO)))
    return 0;

    set_act_time(1);
    do_add_exp(pl);
    return 1;
}


/*
 *Function Name:  do_add_exp()
 *Description:    Gives exp for completing the corsair report quest.
 *Arguments:      pl = player
 */

void
do_add_exp(object pl)
{
    string hname;
    seteuid(getuid(TO));
    pl->set_bit(MORGUL_GROUP, POROS_CORSAIRS_BIT);
    hname = pl->query_real_name();

    pl->add_exp_quest(POROS_CORSAIRS_EXP);
    LOG_QUEST(pl, POROS_CORSAIRS_EXP, "CORSAIR CAPTAIN REPORT");

    command("grin "+hname);
//  Added caps to name in line below.
    command("say You have done well "+ CAP(hname)+".");
    command("say Your service to Morgul has been noted.");
    command("say Go now, and may darkness guide you always!");

    tell_object(pl, "You feel the Dark Lord's presence granting you greater power.\n");
    pl->adjust_alignment(-50);
    pl->remove_prop("_gondor_i_corsair_quest");
}

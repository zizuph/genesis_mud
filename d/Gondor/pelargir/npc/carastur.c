/*
 * /d/Gondor/pelargir/npc/carastur.c
 *
 * The tour and quest master for Pelargir
 *
 * Olorin, July 1995
 *
 * Modification Log:
 *	6 June 1999, Gnadnar:	summon guards if attacked (code
 *		swiped from Elessar's mods to the old ranger),
 *		remember who killed me.
 */
#pragma strict_types

inherit "/d/Gondor/pelargir/npc/pelargir_npc.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/pelargir/lib/defs.h"

#define OFFICE		(PELAR_DIR + "rooms/pel_office")
#define	PEL_GUARD	(PELAR_DIR + "npc/pelargir_guard")

#define TMP_ASKED_FOR_TOUR	"_tmp_asked_for_tour"

#define TOURS	({ "Go and find the corsair that is said to land with " +\
                   "his ship somewhere close to Pelargir.",\
                   "I need information about the activity of the Corsairs! " +\
                   "Go and ask all captains of the ships that come here to " +\
                   "Pelargir for their reports.",\
                   "Go to the militia guard house in Thornlin. " + \
                   "I am expecting reports from the militia there!",\
                   "Go to Hunthor in Minas Tirith. He has important orders for me.",\
                          })


/* don't deal with people who kill carastur or harbour master
 * until next reboot
 */
#define	ADD_KILLER(x) \
    ((PELAR_DIR + "misc/pel_office")->add_killer(x, "Carastur"))
#define	QUERY_KILLER(x) \
    ((PELAR_DIR + "misc/pel_office")->query_killer(x))


int     check_tour(object note, object tp);
int     accept_tour(string str);
string  ask_banner();
string  ask_council();
string  ask_help();
string  default_answer();
string  quest_inform();
void    do_ask_for_note(object tp);
void	do_die(object killer);
void    clone_guards(object attacker);
void    attacked_by(object ob);
int     special_attack(object victim);

int	Guards_summoned;

void
create_pelargir_npc()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_name("carastur");
    set_living_name("carastur");
    set_race_name("human");
    add_name(({"lord", "councillor", "lord councillor",
	"man", "_Pelargir_soldier"}));

    set_title("the Lord Councillor of Pelargir");

    set_adj(({"bald", "black-bearded"}));

    set_long(BSN("The Lord Councillor of Pelargir is a bald black-bearded "
      + "man. He is appointed by the Steward of Gondor and responsible for "
      + "the administration of Pelargir. He also has the duty to assist "
      + "the admiral of the fleet whereever necessary. Due to this he "
      + "is frequently able to provide travellers with tasks."));

    default_config_npc(55 + rnd1);

    set_base_stat(SS_CON, 75 + rnd2);
    set_base_stat(SS_INT, 75 + rnd1 / 2);
    set_base_stat(SS_WIS, 70 + rnd2 + rnd1 / 2);

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_2H_COMBAT, 55);
    set_skill(SS_PARRY,     75);
    set_skill(SS_DEFENCE,   85);
    set_skill(SS_SNEAK,     53);
    set_skill(SS_AWARENESS, 55);
    set_alignment(600);

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    set_cchat_time(7);
    add_cchat("Alarm!");
    add_cchat("Help! I'm being attacked by a maniac!");
    add_cchat("Ok, come on, bastard! I'll beat you up badly!");
    add_cchat("We won't give in to the enemy, killing me won't help!");
    add_cchat("You won't get away with this!");
    add_cchat("You will regret this when you are lying in chains in the prison!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask("help", ask_help);
    add_ask(({"tour","task","quest","job",
              "about tour","about task","about quest","about job",
              "for tour","for task","for quest","for job"}),
        quest_inform);
    add_ask(({"council", "councillor", "lord councillor", }), 
        ask_council);
    add_ask( ({ "banner", "emblem", "flag", }),
	ask_banner);
}

public void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "lsword")->move(TO);
    command("wield all");
    clone_object(ARM_DIR + "studl")->move(TO);
    clone_object(PELAR_DIR + "obj/pel_surcoat")->move(TO);
    command("wear all");
}

void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }
    /* we can be called in response to intro or out of init,
     * so check to be sure we don't intro twice
     */
    if (QUERY_KILLER(tp))
    {
	command("glare " + OB_NAME(tp));
    }
    else if (!(tp->query_met(query_real_name())))
    {
	command("introduce me to "+tp->query_real_name());
        command("say Welcome to Pelargir!");
    }
}

public void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;
    set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
}

void
init_living()
{
    object  tp = TP;

    if (present("Pelargir_Tour_Note",tp))
        set_alarm(1.0, 0.0, &do_ask_for_note(tp));
    if (living(tp) && interactive(tp) && CAN_SEE(TO, tp) &&
        !(tp->query_met(query_real_name())))
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(tp));

    add_action(accept_tour, "accept");
}

void
return_object(object obj, object to)
{
    string  obname = OB_NAME(obj);

    if (obj->id("coin"))
        return;

    command("say I don't think I need that.");
    command("give "+obname+" to "+to->query_real_name());
    if (present(obname, TO))
        command("drop "+obname);
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj) || !living(from))
        return;

    if (obj->id("Pelargir_Tour_Note"))
        set_alarm(0.5, 0.0, &check_tour(obj, from));
    else
        set_alarm(0.5, 0.0, &return_object(obj, from));
}

/*
 *	Answers to questions
 */
string
default_answer()
{
    command("peer " + TP->query_real_name());
    command("say I do not know what you are talking about!");
    command("shrug");
    return "";
}

string
ask_help()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
    command("say Help? You want help with what?");
    command("say Perhaps you are looking for a job?");
    command("peer "+TP->query_real_name());
    return "";
}

string
ask_banner()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
    command("point banner");
    command("say The heraldic blazon for the banner of Pelargir is:");
    command("say \"Azure, in fess three sailing ships Or, in chief a crown Argent.\"");
    command("say A traveller who was learned in heraldic lore and " +
	    "came passing through Pelargir once told me this.");
    return "";
}

string
ask_council()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
    command("say The council consists of a dozen citizens of Pelargir.");
    command("say The councillors are appointed for life by the Steward of Gondor.");
    command("say And by order of the Steward I have been appointed Lord of the Council.");
    command("say In this position, I am responsible for the civilian affairs within the city.");
    return "";
}

/*
 * Functions for the tours
 */
void
do_ask_for_note(object tp)
{
    if (!QUERY_KILLER(tp))
    {
	command("say Hello again!");
	command("say Did you solve the task I gave you?");
	command("say Give me the note, please."); 
	command("smile "+tp->query_real_name());
    }
}

void
reward_tour(object tp, int qno)
{
    int reward;

    set_bin_bits(TOUR_GROUP, PEL_TOUR_FIRST_BIT, PEL_TOUR_NO_OF_BITS, tp, qno);
    command("say Thank you! You have fulfilled the task I gave you!");
    command("shake " + tp->query_real_name());

    switch(qno)
    {
    case 1: 
	reward =  50; break;
    case 2: 
	reward = 100; break;
    case 3: 
	reward = 100; break;
    case 4: 
	reward = 100; break;
    }

    tp->add_exp_quest(reward);
    log_file("mini", tp->query_cap_name()+" did Pelargir tour "
      +qno+" and got "+reward+" xp. " + ctime(time())+".\n");
    tell_object(tp,"You feel a little more experienced.\n");
}

void
check_tour(object note, object tp)
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	command("say I want nothing to do with you, brigand!");
	return;
    }
    if (note->query_player_name() != tp->query_real_name())
    {
        command("say This is not your tour-note! Are you "
          + "trying to cheat?");
        command("glare "+tp->query_real_name());
        log_file("mini", tp->query_cap_name()+" tried to cheat on "
          + "a Pelargir tour for "+CAP(note->query_player_name())
          + ". " + ctime(time())+".\n", 0);
        note->remove_object();
        return;
    }
    if (note->query_tour_no() == query_bin_bits(TOUR_GROUP,
        PEL_TOUR_FIRST_BIT, PEL_TOUR_NO_OF_BITS, tp))
    {
        if (note->query_tour_done())
        {
            reward_tour(tp, note->query_tour_no()+1);
            note->remove_object();
        }
        else
        {
            command("say But you haven't finished the task yet!");
            command("say Oh well - if you decide to try again, "
                  + "you're welcome to ask.");
            note->remove_object();
        }
        return;
    }
    command("say You were not supposed to do that one - "
          + "have you been cheating?");
    command("glare "+tp->query_real_name());
    note->remove_object();
}

string
quest_inform()
{
    int     qno;
    object  tp = TP;
    string  qstr;

    if (QUERY_KILLER(tp))
    {
	command("glare " + OB_NAME(tp));
	command("say I want nothing to do with you, brigand!");
	return "";
    }
    if (objectp(present("Pelargir_Tour_Note", tp)))
    {
        command("peer " + tp->query_real_name());
        command("say But you already have a task that you did not solve yet!");
        return "";
    }

    qno = query_bin_bits(TOUR_GROUP, PEL_TOUR_FIRST_BIT, PEL_TOUR_NO_OF_BITS, tp);

    if (qno >= sizeof(TOURS))
    {
        if (!tp->test_bit("Gondor", PELARGIR_STATUE_GROUP,
                                    PELARGIR_STATUE_BIT))
        {
            command("say One of our citizens has been robbed.");
            command("say His name is Linyenwo.");
            command("say He is living in the Garden District.");
            command("say Go to him and see if you can help him!");
            START_QUEST(tp, "PELARGIR STATUE");
            return "";
        }

        if (!tp->test_bit("Gondor", PELARGIR_REPAIR_DOCK_GROUP, 
                                    PELARGIR_REPAIR_DOCK_BIT))
        {
            command("say I have no more tasks for you at present, "
                + "but why don't you go to the harbour and talk to "
                + "Londhir, the Harbour Master?");
            command("say He is looking for someone to help him "
                + "from time to time.");
            command("say You may be lucky.");
            command("smile");
            START_QUEST(tp, "PELARGIR REPAIR DOCK");
            return "";
        }

        if (!tp->test_bit("Gondor", PELARGIR_LIGHTHOUSE_GROUP, 
                                    PELARGIR_LIGHTHOUSE_BIT))
        {
            command("say The ship captains are complaining about the " +
		    "lighthouse being dark some nights.");
	    command("say If that is true that is serious indeed.");
	    command("frown");
	    command("say Could you ask the keeper of the lighthouse if " +
		    "things are as they should?");
            START_QUEST(tp, "PELARGIR LIGHTHOUSE");
            return "";
        }
        command("say I'm sorry, there are no more tours or quests at the moment.");
        command("say Have you talked to Hunthor, the Master of Advice in Minas Tirith?");
        command("say He is looking for help from time to time.");
        return "";
    }

    command("say This is what you should do:");
    tell_object(tp, BSN(TOURS[qno]));
    command("say If you want to do this task, type 'accept task'");
    tp->add_prop(TMP_ASKED_FOR_TOUR, 1);
    command("smile");
    return "";
}

int
accept_tour(string str)
{
    int     qno;
    object  note,
            tp = TP;

    if (str != "task")
    {
        NFN("Accept what?");
        return 0;
    }
    if (QUERY_KILLER(tp))
    {
	command("glare " + OB_NAME(tp));
	command("say I want nothing to do with you, brigand!");
	return 1;
    }

    if (!tp->query_prop(TMP_ASKED_FOR_TOUR))
    {
        command("say You have to ask for a task first!");
        return 1;
    }

    say(QCTNAME(TP)+" asks the Lord Councillor for a task.\n",TP);
    qno = query_bin_bits(TOUR_GROUP, PEL_TOUR_FIRST_BIT, PEL_TOUR_NO_OF_BITS, tp);

    if (qno >= sizeof(TOURS))
    {
        command("say Sorry, I have no more tasks for you, " + tp->query_race_name()+".");
        return 1;
    }

    command("say Good! Here is a note that will show that you are "
      + "working for me.");
    command("say When you have fulfilled the task, come back to me.");
    note = clone_object(PELAR_DIR + "misc/tournote");
    note->set_tour_no(qno);
    note->set_task(TOURS[qno]);
    note->set_player_name(TP->query_real_name());
    if ((note->move(TP)))
    {
        command("say Hmm. You couldn't carry more. Well, I'll drop it here.");
        note->move(ENV(TO));
    }
    return 1;
}

string *
query_tours()
{
    return TOURS;
}


/*
 * Function name:	do_die
 * Description	:	mask parent to mark our killer
 * Arguments	:	object killer -- cause of death
 *
 */
public void
do_die(object killer)
{
    if (interactive(killer))
    {
	ADD_KILLER(killer);
	killer->add_prop(PEL_I_DID_ATTACK, 1);
    }
    ::do_die(killer);
}


public void
return_to_office()
{
    TO->move_living("back to his office", "/d/Gondor/pelargir/misc/pel_office");
}


/*
 * Function name:	clone_guards
 * Description	:	clone up some protection
 */
public void
clone_guards(object attacker)
{
    int n;
    object tmp;

    FIX_EUID

    if (!objectp(attacker) ||
	ENV(attacker) != TO)
    {
	attacker = TO->query_attack();
    }

    n = sizeof(filter(all_inventory(ENV(TO)), &->id("_pelargir_guard")));
    if (n < 6)
    {
        tmp = clone_object(PEL_GUARD);
        tmp->arm_me();
        tmp->move_living("away", ENV(TO));
        tmp->command("say " + ONE_OF_LIST(({"Now, what's going on here?",
           "I thought I heard fighting!", "Enemies!"})));
        if (TO->query_attack())
        {
            tmp->do_attack(TO->query_attack());
            TO->query_attack()->attack_object(tmp);
        }
        set_alarm(5.0, 0.0, clone_guards);
    }
    else if (objectp(TO->query_attack()) &&
        TO->query_attack()->query_average_stat() >= 100)
    {
        command("emote considers the situation, then retreats.");
        TO->move_living("out the side door", "/d/Gondor/common/void",1);
        set_alarm(500.0, 0.0, return_to_office);
    }
} /* clone_guards */



/*
 * Function name:	attacked_by
 * Description	:	respond to an attack
 * Arguments	:	object ob -- the attacking object
 */
public void
attacked_by(object ob)
{
    if (!Guards_summoned &&
	!present("_pelargir_guard", ENV(TO)))
    {
        clone_guards(ob);
	Guards_summoned = 1;
    }
    ::attacked_by(ob);
} /* attacked_by */



/*
 * Function name:	special_attack
 * Description	:	Called from the external combat object's heart_beat
 *                	routine. We summon guards when attacked.
 * Arguments	:	object victim -- the person we're fighting
 * Returns	:	int -- 0 if we want this round to continue
 *			       1 if we are done with this round
 */
public int
special_attack(object victim)
{
    if (!Guards_summoned &&
	!present("_pelargir_guard", ENV(TO)))
    {
        clone_guards(victim);
	Guards_summoned = 1;
    }
    return ::special_attack(victim);
} /* special_attack */

public void	set_guards_summoned(int g)	{ Guards_summoned = g; }

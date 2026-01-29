/*
 * A barrow wight coded by Arren July 94
 * File: "/d/Gondor/common/quest/nv/wight.c"
 * Not much to say about this one, except I have never
 * coded a spell attack before.
 *
 * Modification log :
 * Revision, Olorin, January 1997
 * Revision, Olorin, March 1997
 * Revision, Stern, February 2000, adapted to genesis gem system
 * Revision, Tigerlily, April, 2004, adapted to ranger recode
 *    references to spells, nightv_scroll and pigeon_scroll
 * Revision, Varian, July 2016, added hints on available rewards
 *    as too many mortals found it confusing and difficult
 * Revision, Carnak, June, 2018, replaced catch_tell with speech_hook to allow
 *    for any conversational verb
 */
#pragma strict_types

inherit "/d/Gondor/common/npc/barrow_wight.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/bits.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define NAME_MASTER             "/d/Gondor/morgul/quest/bsw/master"

#define WEAPON_REWARD           WEP_DIR + "defsword"
#define WEAPON_REWARD_2         WEP_DIR + "old_sword"
#define DAGGER_REWARD           WEP_DIR + "num_dagger"
#define ARMOUR_REWARD           ARM_DIR + "winghelm"
#define ARMOUR_REWARD_2         ARM_DIR + "winghelm"
#define MAGIC_REWARD            ARM_DIR + "stealth_cloak"
#define JEWEL_REWARD            "/d/Genesis/gems/obj/sapphire"

#ifndef NEW_RANGERS_OPEN
#define SPELL_REWARD            (RANGER_DIR + "spells/obj/nightv_scroll")
#define MAGIC_REWARD_2          (RANGER_DIR + "spells/obj/pigeon_scroll")
#endif

#ifdef NEW_RANGERS_OPEN
#define SPELL_REWARD            (RANGERS_SPELL + "obj/nightv_scroll")
#define MAGIC_REWARD_2          (RANGERS_SPELL + "obj/pigeon_scroll")
#endif

#define IN_BARROW               "/d/Gondor/common/quest/nv/inebarrow"

#define WIGHT_ASKED_HELP        "_barrow_wight_asked_help"

#define QUESTER_RECEIVED_TASK    1
#define QUESTER_RETURNED         2
#define QUESTER_TO_BE_PUNISHED   3
#define QUESTER_SPARED           4
#define QUESTER_ONCE_REWARDED    5

// Prototypes:
public void    reset_monster();
public void    retire_to_barrow();

// Global variables:
static int     Part, 
               Year, 
               Tell_Alarm_Id,
               R_Alarm_Id, 
               P_Alarm_Id,
               Ret_Alarm_Id;
static int     Sword_Given, 
               Helm_Given,
               Cloak_Given;
static string  Kingsname;

public void
create_monster()
{
    ::create_monster();
    set_base_stat(SS_STR, 100 + random(20));
    set_base_stat(SS_DEX, 110 + random(20));
    set_base_stat(SS_CON, 110 + random(20));
    set_base_stat(SS_INT, 110 + random(20));
    set_base_stat(SS_WIS,  90 + random(20));
    set_base_stat(SS_INT,  90 + random(20));

    set_skill(SS_DEFENCE,   80);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_PARRY,     80);
    set_all_hitloc_unarmed(30);

    add_prop(LIVE_M_RANGER_NO_BRAWL,  1);
    add_prop(LIVE_I_NO_CORPSE,        1);
    add_prop(LIVE_I_UNDEAD,          70);

    set_tell_active(1);

    enable_reset(10);
    reset_monster();
}

public void
reset_monster()
{
    int    rnd = random(7);

    // We don't want to reset it every reset,
    // and we don't want it to be reset at cloning.

    Cloak_Given = (rnd & 1);
    Sword_Given = (rnd & 2);
    Helm_Given  = (rnd & 4);
}

static void
drain_living()
{
    object *ob;
    int i;
    object me = TO;

    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    for (i = 0; i < sizeof(ob); i++)
    {
        if (!ob[i]->query_prop(LIVE_I_UNDEAD))
        {
             ob[i]->catch_msg(QCTNAME(TO) + " emanates cold, and you "+
             "feel faint.\n");
             ob[i]->add_tmp_stat(SS_CON, -(random(5)+1), random(1000)+100);
        }
    }
}

void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "old_sword")->move(TO);
    command("wield all");

    //  The tattered rags, circlet and protect ring are magical.
    clone_object(ARM_DIR + "tattered_rags")->move(TO);
    clone_object(OBJ_DIR + "gold_ring")->move(TO);
    clone_object(OBJ_DIR + "gold_chain")->move(TO);
    command("wear all");
}

public int query_knight_prestige() { return 1400; }

void
do_die(object killer)
{
    tell_room(ENV(TO), QCTNAME(TO) + " shrivels away to nothing with a "+
    "shriek of despair.\n", TO);
    
    ::do_die(killer);
}

void
no_such_reward(object pl)
{
    R_Alarm_Id = 0;
    if (!objectp(pl))
	return;
    if (ENV(TO) != ENV(pl)) 
	return;
    command("emote hisses: I have ... no ssssuch item...");
    command("emote hisses: Did you want... magicsss?... A sssword?... " +
        "Perhapsss a dagger?... Or armoursss?... Jewelsss?... Richesss?...");
    command("emote hisses: Choosssse again ... but be quick ...");
    tell_room(ENV(TO),"The gaunt shape looks impatient and restless.\n");
}

void
give_reward(object pl, object item)
{
    R_Alarm_Id = 0;

    if (!objectp(item) || !objectp(pl))
    {
	command("emote hisses: That requesssst ... I cannot anssswer ...");
	command("emote hisses: Choossssse anew ... or begone!");
	return;
    }

    if (!objectp(present(pl, ENV(TO))))
    {
	item->remove_object();
	retire_to_barrow();
        return;
    }

    pl->add_prop(WIGHT_ASKED_HELP, QUESTER_ONCE_REWARDED);

    item->move(TO);
    command("emote hisses: Your wissssh ... isss granted ...");
    command("give " + OB_NAME(item) + " to " + pl->query_real_name());
    command("emote hisses: Now begone ... and dissssturb me ... no longer ...");
    command("emote hisses: I ... will plan ... my revenge ...");
    command("emote hisses: The traitor ... king .. "+Kingsname+" .. will ssssuffer ...");
    write_file(REWARD_LOG, sprintf("%s %-29s %-12s (%3d) %6s\n",
				   ctime(time()), "VENGEFUL WIGHT",
				   pl->query_name(), pl->query_average_stat(),
				   item->query_name()));
    remove_alarm(Ret_Alarm_Id);
    Ret_Alarm_Id = set_alarm(3.0, 0.0, retire_to_barrow);
}

static void
punish_cheater(object pl)
{
    int     str_loss, 
	    dex_loss,
	    con_loss;

    P_Alarm_Id = 0;
    remove_alarm(R_Alarm_Id);
    R_Alarm_Id = 0;

    if (!objectp(pl) || !objectp(present(pl, ENV(TO))) ||
        (pl->query_prop(WIGHT_ASKED_HELP) != QUESTER_ONCE_REWARDED))
        return;

    str_loss = pl->query_stat(SS_STR) - 10;
    con_loss = pl->query_stat(SS_DEX) - 10;
    dex_loss = pl->query_stat(SS_CON) - 10;
    pl->add_tmp_stat(SS_STR, (- str_loss), (str_loss * 5));
    pl->add_tmp_stat(SS_DEX, (- dex_loss), (dex_loss * 5));
    pl->add_tmp_stat(SS_CON, (- con_loss), (con_loss * 5));

    write_file(LOG_DIR + "curses", pl->query_name() + " drained of "
      + str_loss + " Str, " + dex_loss + " Dex, and " + con_loss + " Con "
      + "for trying to cheat the Wight, " + ctime(time()) + ".\n");

    pl->catch_msg("The wight glares at you, cackling evilly.\n"
      + "    'So you are a greedy little mortal, eh?'\n"
      + "    'I will sssshow you .... what greed leadssss to!'\n");
    pl->catch_msg("A cold shadow falls over you, and you feel "
      + "weak and helpless like a child.\n");

    pl->add_prop(WIGHT_ASKED_HELP, QUESTER_TO_BE_PUNISHED);
    remove_alarm(Ret_Alarm_Id);
    Ret_Alarm_Id = set_alarm(5.0, 0.0, retire_to_barrow);
    return;
}

void
choose_reward(string what, object pl)
{
    object  item;

    if (!strlen(what))
	return;
    if (!objectp(pl)) 
	return;

    what = lower_case(what);

    if ((R_Alarm_Id && sizeof(get_alarm(R_Alarm_Id))
	 || (pl->query_prop(WIGHT_ASKED_HELP) == QUESTER_ONCE_REWARDED)))
    {
	if (P_Alarm_Id && sizeof(get_alarm(P_Alarm_Id)))
	    return;
	P_Alarm_Id = set_alarm(3.0, 0.0, &punish_cheater(pl));
	return;
    }

    switch (what) 
    {
    case "weapon":
    case "sword":
	if (!Sword_Given) 
	{
	    item = clone_object(WEAPON_REWARD);
	    Sword_Given = 1;
	}
	else 
	    item = clone_object(WEAPON_REWARD_2);
	break;
    case "dagger":
    case "knife":
	item = clone_object(DAGGER_REWARD);
	break;
    case "armour":
	if (!Helm_Given) 
	{
	    item = clone_object(ARMOUR_REWARD);
	    Helm_Given = 1;
	}
	else 
	    item = clone_object(ARMOUR_REWARD_2);
	break;
    case "spells":
    case "spell":
    case "scroll":
	item = clone_object(SPELL_REWARD);
	break;
    case "money":
    case "gold":
    case "wealth":
    case "riches":
	item = clone_object("/std/coins");
	item->set_coin_type("gold");
	item->set_heap_size(18 + random(36));
	break;
    case "jewelry":
    case "jewels":
    case "gems":
	item = clone_object(JEWEL_REWARD);
	item->set_heap_size(5 + random(5));
	break;
    case "magic":
	if (!Cloak_Given)
	{
	    item = clone_object(MAGIC_REWARD);
	    Cloak_Given = 1;
	}
	else
	    item = clone_object(MAGIC_REWARD_2);
	break;
    case "freedom":
	pl->add_panic(300);
	command("emote hisses: Freedom?");
	command("cackle maniac");
	command("emote hisses: Very well ... run! Run, mortal! You are ... free ...");
	pl->run_away();
	break;
    default:
	remove_alarm(R_Alarm_Id);
	R_Alarm_Id = set_alarm(3.0, 0.0, &no_such_reward(pl));
	break;
    }
    if (objectp(item))
    {
	remove_alarm(R_Alarm_Id);
	R_Alarm_Id = set_alarm(3.0, 0.0, &give_reward(pl, item));
    }
}

static void
pull_into_barrow(object pl)
{
    if (!objectp(pl))
	return;
    if (ENV(pl) != ENV(TO)) 
    {
	command("emote hisses: Alassss! My victim ... issss gone!");
	return;
    }
    command("emote hisses: Come ... come ... come ...");
    pl->catch_msg("You feel unable to resist. Willingly you follow, as the gaunt shape\n"+
		  "leads you in through the stone door, into the darkness beyond.....\n");
    pl->move_living("through the stone door, lead by the wight into the barrow", IN_BARROW);
    move_living("through the stone door", IN_BARROW);
    attack_object(pl);
}

static void
tell_quest(object quester)
{
    float  delay = 0.0;

    Tell_Alarm_Id = 0;

    if (!objectp(quester) || !objectp(present(quester, ENV(TO))))
	return;
    if (objectp(query_attack())) 
	return;

    switch (Part++)
    {
    case 0:
	quester->catch_tell("You feel the wight staring at you, its gleaming eyes catching yours.\n");
	command("emote hisses: The traitor ... the King isss a traitor ...");
	quester->catch_tell("The gleaming eyes seem to flare in rage or anger.\n");
        delay = 6.0;
	break;
    case 1:
	command("emote hisses: Yesss ... a traitor ... the King sssent me ... in an ambusssh!");
	quester->catch_tell("The terrifying figure points a bony finger at you.\n"+
            "Terror settles in your soul.\n");
	delay = 5.0;
	break;
    case 2:
	command("emote hisses: The name ... it isss gone ... fffrom my mind ...");
	quester->catch_tell("You cover your ears as the gaunt wight wails.\n"+
            "The sound is frightening, but you detect a tone of sadness and anger in it.\n");
	delay = 7.0;
	break;
    case 3:
	quester->catch_tell("The wight beckons for you with a bony finger.\n");
	command("emote hisses: Find the name ... and I pay ... or ffffail ... and you pay ...");
	quester->add_prop(WIGHT_ASKED_HELP, QUESTER_RECEIVED_TASK);
        START_QUEST(quester, "VENGEFUL WIGHT");
	delay = 5.0;
	break;
    case 4:
	quester->catch_tell("The skeletal figure of the barrow wight motions for you to leave.\n"+
            "You feel a great relief, and an urge to do as the wight wishes!\n");
	command("emote hisses: The name ... the traitorssss name ...");

	if (!Year) 
	    Year = ENV(TO)->query_year();
	if (!strlen(Kingsname) && (Year > 0))
	    Kingsname = "/d/Gondor/morgul/quest/bsw/master"->query_ruler("arnor", Year);
	if (!Ret_Alarm_Id || !sizeof(get_alarm(Ret_Alarm_Id)))
	    set_alarm(20.0, 0.0, retire_to_barrow);

        // Terminate:
        return;
	break;
    default:
        // This should not happen!
	quester->catch_tell("The wight glares at you in silence, waiting for something.\n");
	Part = 0;
        // Terminate:
        return;
    }

    if (delay > 0.0)
    {
	quester->add_panic(10);
	Tell_Alarm_Id = set_alarm(delay, 0.0, &tell_quest(quester));
    }
}

static void
too_slow_answer(object pl)
{
    if (!objectp(pl) || (ENV(pl) != ENV(TO)))
    {
	command("cackle maniac");
	return;
    }

    if (objectp(query_attack()))
	return;

    if (pl->query_prop(WIGHT_ASKED_HELP) == QUESTER_SPARED) 
	return;

    command("emote hisses: No ansssswer ... then ... YOU musssst .... pay!");
    command("cackle maniac");
    pl->add_prop(WIGHT_ASKED_HELP, QUESTER_TO_BE_PUNISHED);
    set_alarm(3.0,0.0, &pull_into_barrow(pl));
}

public varargs void
start_quest(object who)
{
    // Sanity check:
    if (!objectp(who) || !objectp(present(who, ENV(TO))))
        return;

    // If someone else if working on the quest, don't do a thing: 
    if (Tell_Alarm_Id && sizeof(get_alarm(Tell_Alarm_Id)))
        return;

    // OK, at which stage of the quest is the Quester?
    switch (who->query_prop(WIGHT_ASKED_HELP))
    {
    case QUESTER_ONCE_REWARDED:
	if (P_Alarm_Id && sizeof(get_alarm(P_Alarm_Id)))
	    return;
	P_Alarm_Id = set_alarm(3.0, 0.0, &punish_cheater(who));
	break;
    case QUESTER_TO_BE_PUNISHED:
	command("emote hisses: You ... will ... pay!");
	who->catch_tell("The gaunt wight points a bony finger at you.\n"+
			    "You feel the hair rising on your head.\n");
	command("emote hisses: The King ... can wait...for now ... I take you ...");
	who->catch_tell("The wight beckons slowly with its skeletal hand.\n"+
			    "A strange urge comes over you, and you struggle to resist.\n");
	set_alarm(6.0, 0.0, &pull_into_barrow(who));
	break;
    case QUESTER_SPARED:
	who->catch_tell("The wight glares at you, a cold light shining from its eye sockets.\n"+
			   "Then the cold light takes on a gleam of recognition.\n"+
			   "The wight turns slowly away.\n");
	command("emote hisses: Depart ... I ssspared you ... once ...");
	command("emote hisses: Maybe not ... the next time ...");
	tell_room(ENV(TO), "The gaunt figure slowly glides up the stairs, and then\n"+
		  "passes through the closed stone door of the barrow, as if unsubstantial.\n");
	TO->move_living("M", IN_BARROW);
	if (!random(3)) 
	    who->add_prop(WIGHT_ASKED_HELP, QUESTER_TO_BE_PUNISHED);
	break;
    case QUESTER_RECEIVED_TASK:
	who->catch_tell("The gaunt shape of the wight points at you.\n");
	command("emote hisses: His name .... do you have it .... the name " +
            ".... the name of .... the traitor ... traitor King ..");
	who->add_prop(WIGHT_ASKED_HELP, QUESTER_RETURNED);
	command("emote hisses: The name....or you pay ... with your .... life!");
	set_alarm(60.0, 0.0, &too_slow_answer(who));
	break;
    default:
	command("emote hisses: His name....The name....What was his name!");
	tell_room(ENV(TO), "The ghastly figure slowly raises its hand towards you.\n");
        Part = 0;
	Tell_Alarm_Id = set_alarm(5.0, 0.0, &tell_quest(who));
        break;
    }
}

void
want_one_word(object pl)
{
    command("emote hisses: I need only one ... word ...");
    pl->catch_msg("The wight glares at you, waiting for a clear answer.\n");
    pl->add_panic(10);
    return;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    ob->add_prop(WIGHT_ASKED_HELP, QUESTER_TO_BE_PUNISHED);
}

void
wrong_answer(object pl)
{
    command("emote hisses: No! That isss wrong!");
    pl->catch_msg("The wight points at you, and beckons with a bony finger.\n");
    command("emote hisses: Come .... come .... your liiiiffffe ... issss .. mine!");
    pl->add_prop(WIGHT_ASKED_HELP, QUESTER_TO_BE_PUNISHED);
    set_alarm(3.0, 0.0, &pull_into_barrow(pl));
}

public void
retire_to_barrow()
{
    tell_room(ENV(TO),"The wight turns away slowly, and glides up the steps of\n"+
	      "the barrow. Then it passes through the closed stone door,\n"+
	      "as if its incarnation was not of this world.\n");
    TO->move_living("M", IN_BARROW);
}

void 
ask_reward(object pl)
{
    if (!objectp(pl) || (ENV(pl) != ENV(TO)))
	return;
    if (objectp(query_attack())) 
	return;
    if (!pl->test_bit("Gondor",TOUR_GROUP,VENGEFUL_WIGHT_BIT)) 
    {
	pl->set_bit(TOUR_GROUP,VENGEFUL_WIGHT_BIT);
	pl->add_exp_quest(VENGEFUL_WIGHT_EXP);
	LOG_QUEST(pl, VENGEFUL_WIGHT_EXP, "VENGEFUL WIGHT");
	pl->catch_msg("You feel more experienced.\n");
	// If a player solved the quest for the first time,
	// permit him or her to choose freely.
	Cloak_Given = Helm_Given = Sword_Given = 0;
    }
    command("emote hisses: I promisssssed ... to pay ...");
    command("emote hisses: Now choosssse ... your reward ... anything you ... dessssssire ...");
    if (!Ret_Alarm_Id || !sizeof(get_alarm(Ret_Alarm_Id)))
	set_alarm(200.0, 0.0, retire_to_barrow);
}

void
correct_answer(object pl)
{
    if (!objectp(pl) || (ENV(TO) != ENV(pl)))
	return;
    command("emote hisses: Yesss! Yessss! ... "+Kingsname+" isss ... he who sssent me ... in an ambussssh ...");
    pl->add_prop(WIGHT_ASKED_HELP, QUESTER_SPARED);
    command("cackle angrily");
    command("emote hisses: Ssssuffer he sssshall .... ohh yessss ...");
    pl->catch_msg("The gaunt shape gazes at you threateningly. A cold light shines\n"+
		  "in its eyes, but it seems almost to be ... smiling?\n");
    set_alarm(5.0, 0.0, &ask_reward(pl));
}

/*
 * Function name: speech_hook
 * Description  : Whenever someone speaks, this function is called to let the
 *                livings in the room know about the speech. This way we can
 *                avoid the usage of all those costly triggers.
 * Arguments    : string verb - the name of the speech command used. This is
 *                    the command the player typed, query_verb(). For regular
 *                    speech "say" is used even for'.
 *                object actor - the actor of the speech.
 *                string adverb - the adverb used with the speech. If there is
 *                    one, it's prefixed with a space so you can use the
 *                    adverb in your reaction if you please without having
 *                    to parse it further.
 *                object *oblist - the targets of the emotion, if any.
 *                string text - the text that was uttered. Whispering is only
 *                    understood if you are the recipient.
 *                int target - can have three states:
 *                   -1 - speech was directed at someone else
 *                    0 - speech was directed at nobody in particular
 *                    1 - speech was directed at me.
 */
public void
speech_hook(string verb, object actor, string adverb, object *oblist,
            string text, int target)
{
    string *words;
    
    if (objectp(query_attack()))
        return;

    if (target < 0)
        return;
        
    if (!Year) 
        Year = ENV(TO)->query_year();

    if (!strlen(Kingsname) && (Year > 0))
        Kingsname = NAME_MASTER->query_ruler("arnor", Year);
    
    text = lower_case(text);
    
    if (actor->query_prop(WIGHT_ASKED_HELP) == QUESTER_RETURNED)
    {
        words = explode(text, " ");
        if (sizeof(words) > 2) 
        {
            set_alarm(3.0,0.0, &want_one_word(actor));
            return;
        }
        else if (sizeof(words) < 3) 
        {
            if (text == lower_case(Kingsname))
                set_alarm(3.0, 0.0, &correct_answer(actor));
            else
                set_alarm(3.0, 0.0, &wrong_answer(actor));
            return;
        }
        else 
            set_alarm(3.0, 0.0, &want_one_word(actor));
    }
    else if (actor->query_prop(WIGHT_ASKED_HELP) == QUESTER_SPARED) 
    {
        words = explode(text, " ");
        if (sizeof(words) > 1) 
        {
            set_alarm(3.0, 0.0, &want_one_word(actor));
            return;
        }
        
        choose_reward(words[0], actor);
        return;
    }
} /* speech_hook */

/*
 * Call sequence for the quest:
 *
 * edown::enter_inv(ob, from)
 * |--> edown::wight_arrival(ob), ob interactive
 *      |--> wight::start_quest(pl)
 *           stage QUESTER_ONCE_REWARDED:
 *           |--> punish_cheater(who)
 *           stage QUESTER_TO_BE_PUNISHED:
 *           |--> pull_into_barrow(who)
 *           stage QUESTER_SPARED:
 *           |--> set prop to QUESTER_TO_BE_PUNISHED (2 of 3)
 *           stage QUESTER_RECEIVED_TASK:
 *           |--> set prop to QUESTER_RETURNED
 *           |--> too_slow_answer(who)
 *                |--> set prop to QUESTER_TO_BE_PUNISHED
 *                |--> pull_into_barrow(pl)
 *                     |--> attack_object(pl)
 *           stage 0, QUESTER_RETURNED:
 *           |--> tell_quest(who) (Tell_Alarm_Id)
 *                |--> set prop to QUESTER_RECEIVED_TASK
 * wight::catch_tell(str)
 * prop QUESTER_RETURNED
 * |--> want_one_word
 * |--> correct_answer
 *      set prop to QUESTER_SPARED
 *      |--> ask_reward(pl)
 *           |--> retire_to_barrow
 * |--> wrong_answer
 *      set prop to QUESTER_TO_BE_PUNISHED
 *      |--> pull_into_barrow(pl)
 * prop QUESTER_SPARED
 * |--> want_one_word
 * |--> choose_reward
 *      prop QUESTER_ONCE_REWARDED
 *      |--> punish_cheater(pl)
 *           decrease stats
 *           set prop to QUESTER_TO_BE_PUNISHED
 *           |--> retire_to_barrow
 *      all other prop settings
 *      |--> give_reward
 *           set prop to QUESTER_ONCE_REWARDED
 *           |--> retire_to_barrow
 *      |--> no_such_reward
 *
 */

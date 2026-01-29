/*
 * Revisions:
 *   Zielia, Jun 2009: Added Krynn plague check
 *   Lucius, Jul 2011: Added blocking check
 *   Lucius, May 2016: Code cleanups
 *   Lilith, Oct 2021: Added message when someone is trying 
 *                     to break the Gate.
 *   Lilith, Feb 2022: Lock is unpickable now, per Elder request.
 *
 */
#pragma strict_types
inherit "/std/door";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

private int condition = 1000;

public void
create_door(void)
{
    remove_name("door");
    set_door_name("gate");
    add_name(({"_union_gate"}));
    set_adj(({"heavy","thick","steel","black","massive"}));

    add_prop(OBJ_I_WEIGHT, 280000);
    add_prop(OBJ_I_VOLUME, 500000);
    add_prop(DOOR_I_HEIGHT, 500);
    add_prop(OBJ_M_NO_GET, 1);

    set_other_room(HALL+"_w1");
    set_door_id("_Union_entrance_gate");
    set_door_desc("Rising before you, the massive gate is imposing and "+
	"strong. It is formed of a deep black metal that glimmers faintly. "+
	"Completely covering the surface are thousands of intertwining "+
	"carvings in the metal, of faces and shields, birds and "+
	"geometrical shapes, knives and flowers and stars.\n");
    set_open_desc("");
    set_closed_desc("");
    set_pass_command("east");
    set_fail_pass("The black steel gate is shut.\n");
    set_open_command(({"open","push"}));
    set_open_mess(({"pushes the massive steel gate.\nThe gate swings "+
	    "open slowly on silent hinges.\n","The massive gate swings "+
	    "open slowly.\n"}));
    set_fail_open(({"It is open already.\n","It does not move.\n"}));
    set_close_command(({"pull","close"}));
    set_close_mess(({"pulls the massive steel gate closed.\nIt "+
	    "swings shut with a resounding 'clang' that echos down the "+
	    "tunnel.\n","The massive steel gate slowly closes.\n"+
	    "It swings shut with a resounding 'clang' that echos down "+
	    "the hallway.\n"}));
    set_fail_close("It is closed already.\n");

    set_lock_name("indentation");
    set_lock_desc("It is a shallow indentation, the shape of "+
	"a perfect half-sphere.\n");
    set_lock_command("lock");
    set_lock_mess(({"inserts a tiny black sphere into an indentation "+
	    "in the black steel gate.\nThe gate seems to shudder slightly.\n",
	    "The black steel gate seems to shudder slightly.\n"}));
    set_fail_lock(({"It is locked already.\n",
	    "It must be closed first.\n"}));
    set_unlock_command(({"unlock","insert"}));
    set_unlock_mess(({"places a tiny black sphere in the indentation in the "+
	    "black steel gate and turns it slowly.\n",
	    "A strange noise comes from the black steel gate.\n"}));
    set_fail_unlock("It is unlocked already.\n");

    set_open(0);
    set_locked(1);
    set_key(TOKEN_ID);
    set_pick(100);
    set_str(70);
}

public void
do_pick_lock(int skill, int pick)
{
    if (skill > pick)
    {
	write("You fiddle with the small indentation, and finally "+
	    "hear the a low rumble, as if many large mechanisms "+
	    "were at work.\n");
	say("You hear a low rumble from the door, as if many large "+
	    "mechanisms were at work.\n");

	do_unlock_door("");
	other_door->do_unlock_door(check_call(unlock_mess[1]));
    }
    else if (skill < (pick - 50))
    {
	write("You cannot even determine how the lock works, "+
	    "let alone open it.\n");
    }
    else
    {
	write("You fiddle with the small indentation, but cannot "+
	    "seem to make it open.\n");
    }
}

public int
query_condition(void)	{ return condition; }

public int
has_sphere(object who)	{ return objectp(present(TOKEN_ID, who)); }

public int
knock_door(string str)
{
    if (!stringp(str) || !strlen(str))
	return NF(CAP(query_verb()) + " what?\n");

    if (!parse_command(str, ({}), "[on] [the] [black] [metal] 'gate' %s"))
	return NF(CAP(query_verb()) + " what?\n");

    if (query_open())
	return NF("The door is already open, so it would be pointless.\n");

    if (!other_door)
	load_other_door();

    if (!open_status)
    {
	TP->catch_msg(knock_resp[0]);
	say(QCTNAME(TP) + " " + check_call(knock_resp[1]), TP);

	if (objectp(other_door))
	    tell_room(environment(other_door), knock_resp[2]);

	if  (!IS_MEMBER(TP) && !TP->query_wiz_level())
	{
	    if (ENEMY(TP))
	    {
		filter(users(), has_sphere)->catch_tell(
		  "The sound of a gong tolls from your sphere.\n   "+
		  "A vision pierces your mind, that of "+
		  TP->query_cap_name() +", "+
		  LANG_ADDART(TP->query_nonmet_name()) +
		  " and an Enemy of Sybarus, knocking upon the Gate.\n");
	    }
	    else
	    {
		filter(users(), has_sphere)->catch_tell(
		  "The sound of a gong tolls from your sphere.\n   "+
		  "A vision pierces your mind, that of "+
		  TP->query_cap_name() +", "+
		  LANG_ADDART(TP->query_nonmet_name()) +
		  " knocking upon the Gate.\n");
	    }
	}
    }
    else
    {
	TP->catch_msg(knock_fail[0]);
	say(QCTNAME(TP) + " " + check_call(knock_fail[1]), TP);

	if (objectp(other_door))
	    tell_room(environment(other_door), knock_fail[2]);
    }

    return 1;
}

public void
killem(object who)
{
    object nadia = present("nadia", ENV(TO)),
	   cyrus = present("cyrus", ENV(TO));

    if (objectp(nadia) && !nadia->query_attack() && !interactive(nadia))
    {
	nadia->command("scream");
	nadia->command("kill " + OB_NAME(who));
    }

    if (objectp(cyrus) && !cyrus->query_attack() && !interactive(cyrus))
    {
	cyrus->command("curse");
	cyrus->command("kill " + OB_NAME(who));
    }
}

public int
query_broken(void)	{ return query_prop(OBJ_I_BROKEN); }

public int
bash(string str)
{
    int dam;
    object wep;
    string what, with, which, basher;

    if (!str || !strlen(str))
	return NF(CAP(query_verb()) + " what?\n");

    if (!parse_command(str, ({}), "[down] [the] [black] [metal] 'gate' %s", with))
	return NF(CAP(query_verb()) + " what?\n");

    if (query_broken())
	return NF("It is already broken open!\n");

    if (query_open())
	return NF("The door is already open, so it would be pointless.\n");

    if (TP->query_attack())
	return NF("You are too busy fighting right now.\n");

    if (!CAN_SEE_IN_ROOM(TP))
	return NF("It is too dark to see.\n");

    if (TP->query_fatigue() < 20)
	return NF("You are too tired.\n");

    if (!strlen(with))
    {
	write("You try to break down the gate with your bare hands, "+
	    "with little effect.\n");
	say(QCTNAME(TP) + " smashes " + HIS(TP) + " fists against the "+
	    "black steel gate, with no effect.\n");

	TP->add_fatigue(-10);
	return 1;
    }

    if (!parse_command(with, TP, "'with' [my] / [the] %o", wep))
	return NF(CAP(query_verb()) + " the gate with what?\n");

    if (wep->query_wielded() != TP)
    {
	TP->catch_msg("You would need to be wielding " + QSHORT(wep) +
	    " to try to break down the gate with it.\n");
	return 1;
    }
	
	if (!interactive(TP))
		basher = TP->query_race_name();
	else
		basher = TP->query_cap_name();
	if (random(4) == 0)
      filter(users(), has_sphere)->catch_tell(
		  "\nYou feel a burst of intense heat from your sphere.\n   "+
		  "A vision pierces your mind, that of "+
		  basher +", "+ LANG_ADDART(TP->query_nonmet_name()) +
		  ", trying to break through the Gate.\n\n");
	
    TP->catch_msg("You smash your " + QSHORT(wep) +
	" hard against the black gate.\n");
    say(QCTNAME(TP) + " smashes "+ HIS(TP) +" "+ QSHORT(wep) +
	" against the black gate.\n");

    dam = wep->query_pen() + (TP->query_stat(SS_STR) / 5) +
	(wep->query_prop(OBJ_I_WEIGHT) / 1000);

    set_alarm(2.0, 0.0, &killem(TP));

    /* Bludgeoning weapons do by far the worst damage, of course */
    if (wep->query_dt() == W_IMPALE)
	dam /= 100;
    else if (wep->query_dt() == W_BLUDGEON)
	dam *= 3;
    else if (wep->query_dt() == W_SLASH || (wep->query_dt() == (W_SLASH | W_IMPALE)))
	dam /= 20;

    TP->add_fatigue(-15 - random(10));

    /* Resistant weapons won't break */
    if (!wep->query_magic_res(MAGIC_I_RES_MAGIC) &&
	!wep->query_magic_res(MAGIC_I_RES_FIRE) &&
	!wep->query_magic_res(MAGIC_I_RES_EARTH))
    {
	if (random(condition / 100) > dam)
	{
	    tell_room(ENV(TO), CAP(QSHORT(wep)) +
		" shatters upon striking the gate!\n");
	    wep->remove_broken(1);
	    return 1;
	}
	wep->set_dull(wep->query_dull() + 1);
    }

    switch(condition - dam)
    {
    case -1000 .. 10:
	which = "A horrible rending noise comes from the gate, "+
	    "as its hinges are nearly torn out of the wall.\n";
	break;
    case 11 .. 40:
	which = "The gate shudders violently as it is struck.\nIt "+
	    "seems on the verge of collapse.\n";
	break;
    case 41 .. 100:
	which = "The gate shudders and a loud 'clang' echos into the "+
	    "distance.\n";
	break;
    case 101 .. 400:
	which = "The gate shivers beneath a heavy blow.\n";
	break;
    case 401 .. 600:
	which = "The gate shivers slightly, struck with a heavy blow.\n";
	break;
    default:
	which = "The gate sudders a tiny bit.\n";
	break;
    }

    tell_room(ENV(TO), which);
    tell_room(query_other_room(), which);

    condition -= dam;
    if (condition <= 0)
    {
	add_prop(OBJ_I_BROKEN, 1);

	which = "The gate crashes open under the force of the blow, "+
	    "sending dust and debris everywhere.\n";

	do_open_door(which);
	query_other_door()->do_open_door(which);

	environment(this_object())->add_exit("hall_w1", "east", 0, 1, 1);
	environment(query_other_door())->add_exit("entry", "west", 0, 1, 1);
    }

    return 1;
}

public int
close_door(string arg)
{
    if (query_broken())
	return NF("The gate cannot be closed in its current state.\n");

    return ::close_door(arg);
}

public int
pass_door(string arg)
{
    object nadia = present("nadia", ENV(TO));

    if (!objectp(nadia))
	return ::pass_door(arg);

    if (IS_MEMBER(TP))
    {
	if (U_IS_PUNISHED(TP, U_PUNISHED_NOENTER))
	{
	    TP->catch_msg(QCTNAME(nadia)+" stands in your way.\n");
	    nadia->command("us Sorry "+ TP->query_name() +
		". The Elders have told me to deny you entrance.");

	    return 1;
	}

	return ::pass_door(arg);
    }

    if (ENEMY(TP))
    {
	nadia->command("say Over my dead body, scum.");
	TP->catch_msg(QCTNAME(nadia) +" blocks your path.\n");
	say(QCTNAME(nadia)+" blocks "+QTNAME(TP)+" from passing "+
	    "through the gate.\n");

	return 1;
    }

    if (LIST->query_blocked(TP))
    {
	TP->catch_msg(QCTNAME(nadia) +" stands in your way.\n");
	say(QCTNAME(nadia)+" blocks "+QTNAME(TP)+" from passing "+
	    "through the gate.\n");
	nadia->command("say You are Persona Non Grata to Us, "+
	    TP->query_name() +".");
	nadia->command("say Begone from here.");

	return 1;
    }
    /* Allow those that have left back in the Halls
     * if they have been declared a Friend.
     */
    if (FRIEND(TP))
	return ::pass_door(arg);

    if (TP->test_bit("Avenir", GUILD_GROUP, PROHIBIT))
    {
	nadia->command("say You have betrayed us. You have no "+
	    "business being here.");
	TP->catch_msg(QCTNAME(nadia) +" blocks your path.\n");
	say(QCTNAME(nadia)+" blocks "+QTNAME(TP)+" from passing "+
	    "through the gate.\n");

	return 1;
    }

    if (present("nasty_sickness", TP))
    {
	TP->catch_msg(QCTNAME(nadia) +" stands in your way.\n");
	say(QCTNAME(nadia)+" blocks "+QTNAME(TP)+" from passing "+
	    "through the gate.\n");
	nadia->command("say I cannot let you pass whilst you carry "+
	    "such vile impurity, "+ TP->query_name() +".");
	nadia->command("say Return when you have cured that "+
	    "which plagues you.");

	return 1;
    }

    return ::pass_door(arg);
}

public void
init(void)
{
    ::init();

    add_action(bash, "break");
    add_action(bash, "bash");
    add_action(bash, "smash");
    add_action(bash, "batter");
    add_action(bash, "destroy");

    add_action(knock_door, "knock");
}

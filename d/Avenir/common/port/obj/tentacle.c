// Octopus tentacle  (/d/Avenir/common/port/obj/tentacle.c)
// creator(s):       Glinda june -95
// purpose:          What you get when you chop an arm off an
//                   octopus.
/*
 * Revisions:
 * 	Denix,  May 2000: Fixed attach code to prevent runtime errors.
 * 	Lucius, Dec 2017: Code cleanups and runtime error fix.
 */
#pragma strict_types
#include "/d/Avenir/include/defs.h"

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit "/std/leftover";

object target;
string where, subloc_id;
int alarm_id, attached, life = random(5) + 5;

void do_things();

string
set_where()
{
    switch(random(6))
    {
    case 0: where = "right arm"; subloc_id = "tentacle_rarm"; break;
    case 1: where = "left arm";  subloc_id = "tentacle_larm"; break;
    case 2: where = "right leg"; subloc_id = "tentacle_rleg"; break;
    case 3: where = "left leg";  subloc_id = "tentacle_lleg"; break;
    case 4: where = "waist";     subloc_id = "tentacle_wais"; break;
    case 5: where = "chest";     subloc_id = "tentacle_ches"; break;
    }
}

void
create_leftover()
{
    set_name("tentacle");
    add_name(({"arm","octopus_tentacle"}));
    set_adj(({"pale", "slimy","octopus"})[random(2)]);
    set_long("The arm of an octopus. It has been brutally chopped off.\n");
    set_amount(10000);

    add_prop(OBJ_I_WEIGHT, 21000);
    add_prop(OBJ_I_VOLUME, 21000);
    add_prop(OBJ_I_VALUE , 3);

    set_where();
    alarm_id = set_alarm(2.0, 15.0, do_things);
}

void
enter_env(object dest, object old)
{
    set_no_merge(1);
    ::enter_env(dest, old);

    if (living(dest))
       do_things();
}

void
do_things()
{
    if (!life)
	remove_alarm(alarm_id);

    if (!environment())
    {
	remove_alarm(alarm_id);
	set_alarm(1.0, 0.0, remove_object);
	return;
    }

    if (attached)
    {
	target->catch_tell("The tentacle wraps itself even tighter around " +
	  "your " + where + ".\n");
	life--;
	return;
    }

    // find a target to cling to!
    if (interactive(environment()))
	target = environment();
    else
	target = one_of_list(filter(all_inventory(environment()), interactive));

    if (!random(3) && objectp(target))
    {
	// make sure i am in the right place - and then get STUCK
	this_object()->move(target);
	add_prop(OBJ_I_NO_DROP, "The tentacle is stuck around your "+
	    where + ", you have to tear it from yourself first.\n");
	target->catch_tell("The pale, slimy tentacle wraps itself around "+
	    "your " + where + ", you feel the suckers stick to you.\n");
	target->add_subloc(subloc_id,this_object());
	tell_room(environment(target), "The slimy, pale tentacle " +
	    "wraps itself around " + QTPNAME(target) + " " + where +
	    ".\n", target);

	life--;
	attached = 1;
	return;
    }

    life--;
    tell_room(environment(),
	"The slimy, pale tentacle twitches with afterlife reflexes.\n");
}

int
do_tear(string str)
{
    int no_success;
    string vb = query_verb();

    if (str != "tentacle" && str != "off tentacle" && str != "tentacle off")
    {
	NF(capitalize(vb) + " what?\n");
	return 0;
    }

    if (!attached)
    {
	NF("But the tentacle isn't stuck on you.\n");
	return 0;
    }

    if (TP->query_fatigue() < 25)
    {
	TP->catch_tell("You are exhausted. Your efforts are in vain.\n");
	say(QCTNAME(TP) + " almost collapses in an effort to get rid of " +
	  "the tentacle around " + TP->query_possessive() + " " +
	  where + "\n");
	TP->set_fatigue(0);
	return 1;
    }

    if (TP->query_stat(SS_STR) > 85)
	no_success=random(3);
    else
	no_success=random(6);

    if (no_success)
    {
	TP->catch_tell("You struggle to get free from the grasp of the tentacle "+
	  "around your " + where + ", but it seems hopeless.\n");
	say(QCTNAME(TP) + " struggles to get rid of the tentacle around " +
	  TP->query_possessive() + " " + where + ", to no avail.\n");
	TP->add_fatigue(-25);
	return 1;
    }
    remove_prop(OBJ_I_NO_DROP);
    TP->catch_tell("With a huge effort you " + vb + " the tentacle free from " +
      "your " + where + ".\n");
    say(QCTNAME(TP)+ " " + vb + "s the tentacle away from "  +
      TP->query_possessive() + " " + where + ".\n");
    TP->add_fatigue(-25);
    target->remove_subloc(subloc_id,this_object());
    attached = 0;
    target = 0;
    return 1;
}

int
do_eat(string str)
{
    if (str != "tentacle")
        return 0;

    write("Oh, no...the suckers would probably strangle you!\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_eat,  "eat");
    add_action(do_tear, "tear");
    add_action(do_tear, "pull");
    add_action(do_tear, "rip");
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != subloc_id)
	return me->show_subloc(subloc, me, for_obj);

    if (me->query_prop("_temp_subloc_show_only_things"))
	return "";

    if (for_obj == me)
	return "You have a slimy tentacle wrapped around your " + where + ".\n";
    else
	return capitalize(me->query_pronoun()) + " has a slimy tentacle "+
	    "wrapped around " + me->query_possessive() + " " + where + ".\n";
}

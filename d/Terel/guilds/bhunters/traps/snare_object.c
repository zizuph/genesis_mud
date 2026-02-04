/*
 * ANONYMOUS CODE? BAAD! WHO CODED IT?
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "../bhunters.h"

inherit "/std/object";

#define FOOTHOLD_SUBLOC "_foothold_subloc"

string ball_adj;
object snare_shadow;
int fAlarm;


public void set_size(object ball, object shadow)
{
	snare_shadow = shadow;
	add_prop(OBJ_I_WEIGHT, ball->query_prop(OBJ_I_WEIGHT) + 10000);
	add_prop(OBJ_I_VOLUME, ball->query_prop(OBJ_I_VOLUME) + 5000);
	ball_adj = ball->query_component_info();
	E(TO)->add_subloc(FOOTHOLD_SUBLOC, TO);
}

public void init()
{
	::init();
	add_action("open_jaws", "open");
	add_action("open_jaws", "unclasp");
}

create_object()
{
	set_name("trap");
	add_name("foothold");
	
	set_adj("foothold");
	
	set_short("foothold trap");
	set_long("@@long_desc");
	
	add_prop(OBJ_M_NO_DROP, "You would have to unclasp the jaws first.\n");
	add_item("chain", "@@chain_desc");
	add_item(({"jaws", "teeth", "steel jaws"}), "Steel jaws of a foothold trap are clasped around your leg.\n");
	add_item(({"ball", "iron ball"}), "@@ball_desc");
}


void jaws_opened()
{
	E(TO)->catch_msg("With a sudden clang jaws of the trap let go! You're free. " +
		"You quickly discard broken remains of the trap.\n");
	snare_shadow->remove_shadow();
	E(TO)->remove_subloc(FOOTHOLD_SUBLOC);
	remove_object();
}

/* How long will it take for player to open the jaws. */
float calculate_delay(object ob)
{
	return 120.0 - (itof(ob->query_stat(SS_STR)) / 10.0) - (itof(ob->query_skill(SS_FR_TRAP)) / 2.0);
}
	

int open_jaws(string a)
{
	if(!strlen(a) || !parse_command(a, ({}), " [foothold] 'trap' / 'jaws' "))
	{
		notify_fail(capitalize(query_verb()) + " what? Foothold trap maybe? \n");
		return 0;
	}
	if(E(TO)->query_attack())
	{
		notify_fail("You're to busy fighting to attempt freeing yourself.\n");
		return 0;
	}
	write("You start to manipulate with the jaws, attempting to set yourself free...\n");
	say(QCTNAME(TP) + " starts manipulating with the jaws, attempting to set " 
		+ TP->query_objective() + "self free...\n");
	add_action("stop", "", 1);
	float delay = calculate_delay(E(TO));
	fAlarm = set_alarm(delay, 0.0, &jaws_opened());
	return 1;
}

void disturb_open()
{
	if(pointerp(get_alarm((fAlarm))))
	{
		E(TO)->catch_msg("Being forced to defend yourself, you give up trying to " +
			"free yourself from the foothold trap.\n");
		update_actions();
		remove_alarm(fAlarm);
	}
}
	


/* from /std/heap.c */
varargs int stop(string str)
{
    if (query_verb() == "stop")
    {
        update_actions();
	if(pointerp(get_alarm((fAlarm))))
	{
		remove_alarm(fAlarm);
		write("You give up trying to free yourself.\n");
		say(QCTNAME(this_player()) + " gives up trying to free " + TP->query_objective() + "self.\n");
		return 1;
	}
    }

    /* Allow wizards and allow commands that are allowed. */
    if (this_player()->query_wiz_level() ||
        CMDPARSE_PARALYZE_CMD_IS_ALLOWED(query_verb()))
    {
        /* When quitting, update the actions, so people can drop stuff. */
        if (query_verb() == "quit")
        {
            update_actions();
        }
        return 0;
    }

    write("You currently completely focused on trying to free youself from a foothold trap " +
		"use 'stop' if you want to do something else.\n");
    return 1;
}

string chain_desc()
{
	return "A 6 feet long chain connects jaws clasped around your leg to a " + ball_adj + " on the ground.\n";
}

string long_desc()
{
	return "Sharp teeth of foothold trap's jaws are clasped around your leg, trap is connected to a " +
		ball_adj + " iron ball, which makes moving both painful and tiresome for you.\n";
}

string ball_desc()
{
	return capitalize(ball_adj) + " iron ball. It looks very heavy.\n";
}

string show_subloc(string subloc, object me, object for_obj)
{
	string resoult = "A steel jaws of a foothold trap are clasped around ";

	if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
		return "";

	if( for_obj == me )
		resoult += "your";
	else 
		resoult += me->query_possessive();
	resoult += " leg.\n";

	return resoult; 
 
}

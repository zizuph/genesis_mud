#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "../bhunters.h"

inherit "/std/object";

#define PAINT_SUBLOC "_paint_subloc"

object snare_shadow;

public void init()
{
	::init();
	add_action("clean_paint", "clean");
	add_action("clean_paint", "wash");
}

create_object()
{
	set_name("_paint_");
	add_prop(OBJ_I_VOLUME, 0);
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_NO_DROP, 1);
	add_prop(OBJ_I_NO_GIVE, 1);
	set_no_show();
}

int clean_paint(string a)
{
	if(!strlen(a) || !parse_command(a, ({}), " 'me' / 'myself' [from] [paint] "))
	{
		notify_fail(capitalize(query_verb()) + " youself from paint maybe? \n");
		return 0;
	}
	if(E(TP)->query_prop(OBJ_I_CONTAIN_WATER) == 0)
	{
		notify_fail("You need some current water to do that.\n");
		return 0;
	}
	write("You clean yourself from the paint.\n");
	say(QCTNAME(TP) + " cleans " + TP->query_objective() + "self from red paint.\n");
	TP->clean_me();
	E(TO)->remove_subloc(PAINT_SUBLOC);
	remove_object();
	return 1;
}

void
enter_env(object to, object from)
{
	::enter_env(to, from);

	/* Sanity check */
	if (!objectp(to) || !living(to))
	{
		to->clean_me();
		remove_object();
		return;
	}
	to->add_subloc(PAINT_SUBLOC, TO);
}

string show_subloc(string subloc, object me, object for_obj)
{
	if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
		return "";
	
	if(for_obj == me)
		return "You are covered with red paint. You should clean yourself in current water.\n";
	
	return capitalize(me->query_pronoun()) + " is covered with red paint.\n";
}

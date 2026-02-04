#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit BHTRAPS + "trap";

public void create_trap()
{
	configure_trap(600, 900, 950, 1.0, 1.0, "paint");
}

string *query_component_list()
{
	return ({"trigger", "paint", ""});
}

string *query_set_phases()
{
	return ({
			({
				"You hide the trigger-mechanism on the ground.\n",
				" hides something small and shiny.\n"
			}),
			({
				"You place the bucket of paint and conceal it carefully.\n",
				" hides a bucket of paint.\n"
			})
		});
}

public string *query_disarm_desc()
{
	return ({"You disable the trigger mechanism, and pick it up.\n",
		" disarms a trap.\n"});
}

public void trap_me(object ob)
{
	FIX_EUID;
	ob->catch_msg("\nYou hear a metalic 'click', and you find yourself covered with thick liquid of intenstive " +
		"smell.\n\n");
	tell_room(E(ob), QCTNAME(ob) + " looks down as if he heared something, you hardly keep yourself from laughing, " +
		"as bucket of paint falls on his head.\n", ob);
	object paint_shadow = clone_object(BHTRAPS + "paint_shadow");
	paint_shadow->trap_me(ob);
}

public string query_set_desc()
{
	if(!query_spoiled())
		return "A sophisticated triggering mechanism is connected to thin wire tied to a bucket of paint.\n";
	return "It seems like someone was trying to do a practical joke here, but he haven't finished.\n";
}
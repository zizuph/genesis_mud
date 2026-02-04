#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit BHTRAPS + "trap";

public void create_trap()
{
	configure_trap(600, 800, 950, 1.0, 1.0, "dartgun");
}

string *query_component_list()
{
	return ({"trigger", "blowpipe", "dart"});
}

string *query_set_phases()
{
	return ({
			({
				"You hide the trigger-mechanism on the ground.\n",
				" hides something small and shiny.\n"
			}),
			({
				"You load the blowpipe with poisoned dart.\n",
				" loads a blowpipe.\n"
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
	ob->catch_msg("\nYou hear a metalic 'click', and feel a sudden pinch on your neck. With a bit of supprise you find a small dart "+
		"pointing from it.\n\n");
	tell_room(E(ob), QCTNAME(ob) + " suddenly raises his hand to his neck. Pulling out something appearing to be some kind of "+
		"dart from it.\n", ob);
	object poison = clone_object(BHTRAPS + "poison");
	poison->move(ob);
	poison->start_poison();
}

public string query_set_desc()
{
	if(!query_spoiled())
		return "A sophisticated triggering mechanism is connected to concealed blowpipe.\n";
	return "It seems like someone was trying to set dartgun trap here, but he haven't finished.\n";
}
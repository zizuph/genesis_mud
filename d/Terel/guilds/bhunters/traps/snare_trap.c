#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>

inherit BHTRAPS + "trap";

public void create_trap()
{
	configure_trap(650, 900, 800, 1.0, 1.0, "foothold");
}

string *query_component_list()
{
	return ({"snare", "chain", "ball"});
}

string *query_set_phases()
{
	return ({
			({
				"You place the foothold trap on the ground, and cover it with leaves.\n",
				" places a foothold trap on the ground and covers it with leaves.\n"
			}),
			({
				"You attach chain to one of the trap's jaws, now you need to hitch "
					+ "the other end to a ball.\n",
				" attaches chain to one of the trap's jaws.\n"
			})
		});
}

public string *query_disarm_desc()
{
	return ({"You cut a wire between the jaws, and the trap is now harmless.\n",
		" disarms a foothold trap.\n"});
}

public int can_be_placed(object ob)
{
	return 1 - ob->query_prop(ROOM_I_INSIDE);
}

public void trap_me(object ob)
{
	FIX_EUID;
	object ball = query_element("ball");
	object effect_shadow = clone_object(BHTRAPS + "snare_shadow");
	effect_shadow->trap_me(ob, ball);
}

public string query_set_desc()
{
	string str = "A foothold trap, commonly used for hunting bears is set on the ground, covered with "+
			"leaves and dust.\n";
	if(!query_spoiled())
		return str;
	return str + "You notice that it hasn't been set properly, and it seems quite harmless.\n";
}
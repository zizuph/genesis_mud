
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_er_room()
{
    set_area("somewhere in the Lone-lands on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("rugged downs");
    set_grass("sparse, dry");
    set_treetype("aspen");

    set_extraline("All around you the surrounds are dry and "+
    "barren from more than a millenia of erosion. These are "+
    "the Lone-lands, almost devoid of flora and fauna, "+
    "practically a waste-land. "+
    "The road continues to the west and east from here.");

    add_exit(ER_DIR + "erb32",  "west", 0, 1);
    add_exit(ER_DIR + "erb34",  "east", 0, 1);
/*  add_exit(ER_DIR + "erb33n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb33s", "south", 0, 2, 1);
*/
    add_lonelands();

}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}

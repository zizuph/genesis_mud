#pragma save_binary
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
    set_area("some distance from the Last Bridge on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("rugged downs");
    set_grass("sparse, dry");
    set_treetype("aspen");

    set_extraline("All around you the surrounds are dry and "+
      "barren from more than a millenia of erosion. These are "+
      "the Lone-lands, almost devoid of flora and fauna, "+
      "practically a waste-land. A dark strip of green across "+
      "the horizon to the southeast gives evidence to the great "+
      "Hoarwell river, its waters giving life to the dry lands. "+
      "The road continues to the west and southeast from here.");

    add_item(({"dark strip","strip","green","trees","horizon"}),
      "Along the horizon you see a dark strip of green, indicating "+
      "to you a water source, namely the Hoarwell, providing "+
      "the necessary moisture for trees to grow.\n");
    add_item(({"river","hoarwell river","waters"}),
      "The green strip of trees almost assuredly is a sign of a "+
      "river, you're sure its the waters of the Hoarwell river"+
      ".\n");

    add_exit(ER_DIR + "erb35",  "west", 0, 1);
    add_exit(ER_DIR + "erb37",  "southeast", 0, 1);
    /*  add_exit(ER_DIR + "erb37n", "east", 0, 2, 1);
	add_exit(ER_DIR + "erb36n", "north", 0, 2, 1);
	add_exit(ER_DIR + "erb36s", "south", 0, 2, 1);
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

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "sw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_er_room()
{
    set_area("near the Midgewater Marshes on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("broken lowland");
    set_grass("dry, clumpy");
    set_treetype("aspen");

    set_extraline("The Midgewater Marshes are now away from the "+
    "roadside to the west, the stench and pall still visible from "+
    "here. To the east and north the wet lowland fields are rising, "+
    "as the barren downs take over, leaving the damp earth below. "+
    "The road continues to the southwest and east from here.");

    add_item(({"marshes","midgewater marshes","haze"}),
      "The Midgewater Marshes have split from the road "+
      "and headed north, leaving the fields around it still "+
      "soaked and stinking of the marsh.\n");
    add_item("fields",
      "The fields around you are rather damp, but the further "+
      "they spread east the dryer they become as they gain "+
      "elevation and escape from the marshes.\n");
    add_item("stench",
      "The Midgewater Marshes are far off now where the smell "+
      "is no longer overpowering. As occasionally as the breeze "+
      "stirs, you catch a reminder of its offensive odor.\n");
    add_item(({"hills","downs","south downs"}),
      "Crawling closer to the road from the south are "+
      "the South Downs, pushing the fields aside as they try to "+
      "meet with the Great Eastroad. The further you travel west, "+
      "the closer they come. The hills are rather bare of trees, "+
      "mostly left to wild grasses and weeds to provide cover.\n");

    add_exit(ER_DIR + "erb17",  "east", 0, 1);
    add_exit(ER_DIR + "erb15",  "southwest", 0, 2);
    add_exit(ER_DIR + "erb15n1", "west", 0, 1);
    add_exit(ER_DIR + "erb15n2", "northwest", 0, 2);
//    add_exit(ER_DIR + "erb16s", "south", 0, 2, 1);

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

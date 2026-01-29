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
    set_area("far from Weathertop on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("rugged downs");
    set_grass("sparse, dry");
    set_treetype("aspen");

    set_extraline("Weathertop sits distant in the west where "+
    "the road winds south around its circumference, and to your "+
    "northwest you can make out the Weather Hills. All around "+
    "you the surrounds are dry and more barren from more "+
    "than a millenia of erosion. "+
    "The road continues to the southwest and east from here.");

    add_item("weathertop",
      "On the west horizon is Amon Sul, "+
      "the ancient watchtower of an age gone by. No details "+
      "are visible at this distance, but just being within "+
      "sight of it gives you a feeling of being watched.\n");
    add_item(({"hills","weather hills"}),
      "Looking northwest you "+
      "are able to drink in the view of the Weather Hills. "+
      "You guess that they are less than a days walk to your "+
      "north, a line of rugged and forested hills that run "+
      "northwest into the distance.\n");
    add_item("vegetation",
      "At your current elevation, the dry earth and strong "+
      "winds are any but forgiving on the flora, what does "+
      "survive is typically tough grasses and small thorny "+
      "bushes, an indication of how tough life is out "+
      "here.\n");
    add_item("earth",
      "With the windswept elevation and little moisture the "+
      "earth below you is dry and cracked, leeched of "+
      "nutrients and eroded.\n");

    add_exit(ER_DIR + "erb23",  "southwest", 0, 1);
    add_exit(ER_DIR + "erb25",  "east", 0, 1);
/*  add_exit(ER_DIR + "erb23n", "west", 0, 2, 1);
    add_exit(ER_DIR + "erb24n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb24s", "south", 0, 2, 1);
*/
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

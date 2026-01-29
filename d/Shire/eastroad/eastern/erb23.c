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
    set_area("not far from Weathertop on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("rugged downs");
    set_grass("sparse, dry");
    set_treetype("aspen");

    set_extraline("Weathertop sits commanding in the west where "+
    "the road winds south around its circumference, and north of "+
    "it you can see the Weather Hills. Elsewhere around you the "+
    "surrounds become even dryer and more barren from more than a "+
    "millenia of erosion. "+
    "The road continues to the west and northeast from here.");

    add_item("weathertop",
      "Standing off to the west is Amon Sul, "+
      "the ancient watchtower of an age gone by. Its bald top "+
      "is all that is visible at this distance, but just being "+
      "within sight of it gives you a feeling of being watched.\n");
    add_item(({"hills","weather hills"}),
      "Your view clear past the east side of Weather Top, you "+
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

    add_exit(ER_DIR + "erb22",  "west", 0, 1);
    add_exit(ER_DIR + "erb24",  "northeast", 0, 1);
/*  add_exit(ER_DIR + "erb24s", "east", 0, 2, 1);
    add_exit(ER_DIR + "erb23n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb23s", "south", 0, 2, 1);
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

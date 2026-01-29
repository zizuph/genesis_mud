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
    set_area("at the foot of Weathertop on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("broken downs");
    set_grass("dry, clumpy");
    set_treetype("aspen");

    set_extraline("You stand at the southeast edge of Weathertop as "+
    "it towers above you, sparse vegetation failing to soften "+
    "its ominous demeanor. You can make out nothing interesting "+
    "on its bald top from here, but do see some aspen groves "+
    "that grow around the base of the ancient watchpost. "+
    "The road continues to the west and northeast from here.");

    add_item("weathertop",
      "Looming over you to the northwest is Amon Sul, "+
      "the ancient watchtower of an age gone by. Its bald top "+
      "at this distance is obvious, and just being within "+
      "sight of it gives you a feeling of being watched.\n");
    add_item(({"hills","weather hills"}),
      "Your view clear down the east side of Weather Top, you "+
      "are able to drink in the view of the Weather Hills. "+
      "You guess that they are less than a days walk to your "+
      "north, a line of rugged and forested hills that run "+
      "northwest into the distance.\n");
    add_item(({"trees","tree","grove","groves","aspen"}),
      "In apparent rebellion against the dry and cracked "+
      "earth that surrounds the Weathertop, some resolute "+
      "groves of aspen find places to set their roots and "+
      "survive, on slopes and dales around the base of the "+
      "monolith.\n");
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

    add_exit(ER_DIR + "erb20",  "west", 0, 1);
    add_exit(ER_DIR + "erb22",  "northeast", 0, 1);
/*  add_exit(ER_DIR + "erb22s", "east", 0, 2, 1);
    add_exit(ER_DIR + "erb21n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb21s", "south", 0, 2, 1);
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

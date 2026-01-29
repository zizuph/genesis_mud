#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "nw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_er_room()
{
    set_area("close to the Last Bridge on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("river valley");
    set_grass("lush, green");
    set_treetype("willow");

    set_extraline("All around you to the west and north the dry "+
    "Lone-lands dominate, the broken, leeched earth barely able "+
    "to support the sparse grasses and plants that manage to survive "+
    "there. To the southeast the road starts downward, into the "+
    "valley where the great Hoarwell river and the Last bridge "+
    "await. The dark green of the forests across the river now "+
    "command your attention to the east and south. "+
    "The road continues to the northwest and southeast from here.");

add_item(({"southeast","valley"}),
"The road meanders southeast from the elevated Lone-lands "+
"into a valley obviously carved by the great river.\n");
add_item(({"hoarwell","river","hoarwell river"}),
"Rushing and peaking in its hurry southwest, the great Hoar"+
"well river seems to carve its way along an avenue of "+
"weeping willows, challenged only by a span that must be "+
"the \"Last Bridge\".\n");
add_item(({"bridge","span","last bridge"}),
"The ancient stone bridge, known as the Last Bridge, "+
"here dares challenge the Hoarwell's fury, its foundations "+
"seemingly immovable by river or time. Massive, smooth "+
"blocks of granite form a span easily wide enough for two "+
"wagons to pass by each other.\n");
add_item(({"forests","forest","trees","willows"}),
"The shade and nourishment provided by the river valley "+
"gives bloom to a healthy run of willows and other trees"+
", and on the east side of the river the forests thicken "+
"and become the dreaded Trollshaws.\n");

    add_exit(ER_DIR + "erb36",  "northwest", 0, 1);
    add_exit(ER_DIR + "erb38",  "southeast", 0, 1);
/*  add_exit(ER_DIR + "erb36s", "west", 0, 2, 1);
    add_exit(ER_DIR + "erb38n", "east", 0, 2, 1);
    add_exit(ER_DIR + "erb37n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb37s", "south", 0, 2, 1);
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

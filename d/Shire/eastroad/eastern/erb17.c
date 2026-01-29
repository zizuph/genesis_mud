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
    set_area("far from Weathertop on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("broken downs");
    set_grass("dry, clumpy");
    set_treetype("aspen");

    set_extraline("You're now approximately halfway between the "+
    "Midgewater Marshes and Weathertop. Far to the west you can "+
    "just make out the haze of the marshes, and Weathertop is now "+
    "visible above the dry downs, where you know the Weather "+
    "Hills stand in line behind it. "+
    "The road continues to the west and east from here.");

    add_item(({"marshes","midgewater marshes","haze"}),
      "The Midgewater Marshes are now a distant apparition "+
      "on the western, the fields getting dryer the further "+
      "away and higher in elevation they get.\n");
    add_item("fields",
      "The fields around you are slightly damp, but the further "+
      "they spread east the dryer they become as they gain "+
      "elevation and escape from the marshes.\n");
    add_item(({"hills","downs","south downs"}),
      "On the southwest horizon the South Downs creep towards the "+
      "road, getting closer until they meet the road at the "+
      "southern most point of the Midgewater Marshes. Due south "+
      "they quickly fall away and fade.\n");

    add_exit(ER_DIR + "erb16",  "west", 0, 1);
    add_exit(ER_DIR + "erb18",  "east", 0, 1);
/*  add_exit(ER_DIR + "erb17n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb17s", "south", 0, 2, 1);
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

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
    set_area("near the Midgewater Marshes on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("wet lowland");
    set_grass("wet long");
    set_treetype("willow");

    set_extraline("The Midgewater Marshes come close to the "+
    "roadside to the west, the stench and haze obscures your "+
    "vision. To the east and north the wet lowland fields spread out, "+
    "except to the south where rolling hills lift the earth from the "+
    "damp earth below. The road continues to the west and northeast "+
    "from here.");

    add_item(({"marshes","midgewater marshes","haze"}),
      "The Midgewater Marshes come right up to the edge of the road "+
      "and you fear that if you left the road you would "+
      "instantly be lost amongst the haze that hangs over the "+
      "marshes like a blanket.\n");
    add_item("stench",
      "The Midgewater Marshes give off a potent stench like rotten "+
      "eggs as most marshes do, however, there is definately a "+
      "perception of something much more sinister there.\n");
    add_item(({"hills","downs","south downs"}),
      "Crawling closer and closer to the road from the south are "+
      "the South Downs, pushing the fields aside as they try to "+
      "meet with the Midgewater Marshes. The hills are rather "+
      "bare of trees, mostly left to wild grasses and weeds to "+
      "provide cover.\n");


    add_exit(ER_DIR + "erb14",  "west", 0, 1);
    add_exit(ER_DIR + "erb16",  "northeast", 0, 1);
/*  add_exit(ER_DIR + "erb16s", "east", 0, 2, 1);
    add_exit(ER_DIR + "erb15n", "north", 0, 2, 1);
    add_exit(ER_DIR + "erb15s", "south", 0, 2, 1);
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
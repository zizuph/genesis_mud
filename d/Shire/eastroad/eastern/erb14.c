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
    set_area("beside the Midgewater Marshes on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("swamp");
    set_grass("wet long");
    set_treetype("willow");

    set_extraline("The Midgewater Marshes come right up to the "+
    "roadside, the stench and haze obscuring your vision. To the "+
    "south the hills that were closing in now encroach on the road. "+
    "The road continues to the southwest and east from here.");

    add_item(({"marshes","midgewater marshes","haze"}),
      "The Midgewater Marshes come right up to the edge of the road "+
      "and you fear that if you left the road you would "+
      "instantly be lost amongst the haze that hangs over the "+
      "marshes like a blanket. The marshes seem to make a final "+
      "lunge for the road here, and the road makes a diversion "+
      "to the south to avoid it.\n");
    add_item("stench",
      "The Midgewater Marshes give off a potent stench like rotten "+
      "eggs as most marshes do, however, there is definately a "+
      "perception of something much more sinister there.\n");
    add_item(({"hills","downs","south downs"}),
      "Crawling closer and closer to the road from the south are "+
      "the South Downs, pushing the fields aside as they try to "+
      "meet with the Midgewater Marshes. The hills are rather "+
      "bare of trees, mostly left to wild grasses and weeds to "+
      "provide cover.\n");;

    add_exit(ER_DIR + "erb13",  "southwest", 0, 1);
    add_exit(ER_DIR + "erb15",  "east", 0, 1);
//    add_exit(ER_DIR + "erb13n", "west", 0, 2, 1);
    add_exit(ER_DIR + "erb14n1", "north", 0, 2);
//    add_exit(ER_DIR + "erb14s", "south", 0, 2, 1); */

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
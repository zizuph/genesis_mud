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
    set_area("between the Chetwood and the Midgewater Marshes on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("open field");
    set_grass("wet long");
    set_treetype("willow");

    set_extraline("The dense oak forest is now barely visible to the "+
      "northwest, where in all other directions the view is pretty clear, "+
      "except to the east where you can make out the pall hanging over "+
      "the Midgewater Marshes. The road continues to the west and "+
      "southeast from here.");

    add_item(({"forest","oak forest","the chetwood","trees"}),
      "The shadow of the Chetwood envelopes the Great East "+
      "road to the northwest, its ancient oaks looking ominous "+
      "and gloomy from a distance.\n");
    add_item(("fields"),
      "Besides the Chetwood to the northwest, and the Midgewater "+
      "marshes to the east, there are fields of long green grass "+
      "in all directions. South of the road the landscape gently "+
      "undulates until it reaches the South Downs, getting "+
      "closer until they approach the road further to the "+
      "southeast. You notice the fields to the north of the road "+
      "are getting wetter and muddier as they drop in elevation "+
      "and get closer to the Midgewater Marshes.\n");
    add_item(({"hills","downs","south downs"}),
      "Sitting on the south horizon are the south downs, slowly "+
      "creeping up on the Great East road until they meet in the "+
      "distance to the southeast.\n");
    add_item(({"pall","marsh","marshes","midgewater marshes"}),
      "The faint whiff of something putrid fills the air as you "+
      "get closer to the Midgewater Marshes. The marshes get closer " +
      "to the road the further you go east, "+
      "until the road has to make a final twist around the "+
      "marshes southernmost point.\n");

    add_exit(ER_DIR + "erb6",  "west", 0, 1);
    add_exit(ER_DIR + "erb8",  "southeast", 0, 1);
//    add_exit(ER_DIR + "erb8n", "east", 0, 2, 1);
	add_exit(ER_DIR + "erb7n1", "north", 0, 2);
//	add_exit(ER_DIR + "erb7s", "south", 0, 2, 1);

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

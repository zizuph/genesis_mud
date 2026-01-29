/* created by Aridor 12/20/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

#include <ss_types.h>

void
create_splains_room()
{
    set_short("On the rock");
    set_long(BS("You are standing on the big rock in the river. Further inside the " +
		"gorge you can see a waterfall. It is quite some distance away.",SL));

    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is comes from the narrow valley to your northwest and flows " +
	     "around the rock you are standing on to the east onto the plains.\n");
    add_item(({"waterfall"}),
	     "The waterfall is to you northwest. You believe it could be possible to dive " +
	     "into the waterfall, but then again why would you want to do that?\n");
    add_item(({"valley","gorge"}),
	     "The valley is so narrow that there is only room for the river and it " +
	     "looks impossible to go in on foot.\n");
    add_cmd_item(({"into waterfall","into water","into the water","into the waterfall"}),
		 ({"dive","jump"}), "@@jump_into_waterfall");

    set_noshow_obvious(1);
    add_exit(ROOM + "plain18","south",0,3);
    add_exit(ROOM + "river1","east",0,3);
    add_exit(ROOM + "mount2","southwest",0,3);
}


string
jump_into_waterfall()
{
  if (TP->query_base_stat(SS_DEX) < random(30) + 25)
    {
      write("You dive into the waterfall. Unfortunately you don't even get this " +
	    "far and are washed away by the water down the river.\n");
      TP->move_living("down the river",ROOM + "in_water",1,1);
    }
  else
    {
      write("You dive into the water. It seems that you can grasp a rock under the " +
	    "waterfall and are able to pull yourself up into a small cave behind the " +
	    "water.\n");
      TP->move_living("through the waterfall",ROOM + "waterfall",0,0);
    }
  return "";
}

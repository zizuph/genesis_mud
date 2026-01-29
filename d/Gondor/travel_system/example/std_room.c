/*
 * Standard room for the forest area.
 * Written by Toby
 */
#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include DEFS_LOCATIONS

inherit EXAMPLE_STD_ROOM;

nomask public void
make_me_forest(string extra_long)
{
  // This is where forest-specific things go.

  switch (random(2))
  {
  case 0:
    set_long("You are walking in an example forest filled with beautiful " +
             "pines. The limbs of the huge trees looks as if they try to " +
             "reach the sky and the foilage is rather dense making the light " +
	     "a bit dim. " + extra_long + "\n");
    break;
  case 1:
    set_long("You are in a great pine forest serving as an example for wizards " +
             "trying to understand the travelling system. The trees are huge, " +
             "the largest probably several centuries old. " + extra_long + "\n");
    break;
  case 2:
    set_long("You are in an example forest, surrounded by pine trees, their " +
             "massive trunks standing firmly on the ground. " + extra_long + "\n");
    break;
  }
  
  set_short("In an example forest filled with pines");
  
  add_item(({ "forest", "tree", "trees" }),
	   "This forest consists mostly of tall pines, their tops " +
	   "reaching high for the clear blue sky overhead.\n");
  add_item(({ "ground", "underbrush", "floor", }),
	   "The floor of this forest is covered with rocks, moss and " +
	   "different shrubs. If you knew what to look for you could " +
	   "probably find a handful of different useful plants there.\n");
}

nomask public void
make_me_road(string extra_long)
{
  // This is where road-specific things go.

  set_long("You are walking on an example road in a pine forest. The " +
           "foliage of tall trees of the forest provide a nice shelter " +
           "from the böazing sun and making travelling the road rather " +
           "nice and comfortable. " + extra_long + "\n");
  
  set_short("On a road in a pine example forest");

  add_item(({ "ground", "road", }),
	   "You are standing on a dirt road. It looks quite " +
	   "well-travelled.\n");
}

public void
create_subpart_east_room()
{
  
}

nomask public void
create_example_room()
{
  // This is where global things go..

  set_this_location(AREA_EXAMPLE_FOREST);
  add_known_location(AREA_EXAMPLE_FOREST, SUBAREA_EAST_EXIT);
  add_known_location(AREA_EXAMPLE_FOREST, SUBAREA_WEST_EXIT);
  add_known_location(AAREA_EXAMPLE_FOREST, SUBAREA_PATH_ENTR);

  create_subpart_east_room();

  reset_room();
}

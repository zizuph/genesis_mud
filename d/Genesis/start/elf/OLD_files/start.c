/*
 * Generic Elvish start.
 * Actual starting location.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A beach");
  set_long(""+
   "Looking at the inner sea of Habros, you feel the tranquility surrounding\n"+
   "this beach.  It is called Cuivienen.  Here the awakening  of  the  Elven\n"+
   "race took place.  As you look around a bit, you see a huge forest to the\n"+
   "east of this beach.  It seems to be a rather dense forest which leads to\n"+
   "an mountain range in the far east, leading north.\n"+
   "As you look around a bit, you notice two paths, one  leading  north  and\n"+
   "another leading south.  A portal of trees seems to invite you  to  enter\n"+
   "the forest.  You hear some fine music.\n");
  add_item("sea",
   "Never have you seen something like this.  This sea is so blue, that  you\n"+
   "can't imagine any other like this.\n");
  add_item(({"path", "paths"}),
   "Looking at the paths, you see that one is heading north, leading to some\n"+
   "extension of this beach.  Far in the northwest you see some white shape.\n"+
   "The other path seems to be leading to the south into a rather dark  part\n"+
   "of the forest.\n");
  add_item("portal",
   "The shape of the trees above the small  path  leading  into  the  forest\n"+
   "resembles the form of a portal pretty well.\n");
  add_exit(STANDARD_DIR + "beach", "north");
  add_exit(STANDARD_DIR + "forest1", "east");
  add_exit(STANDARD_DIR + "forest2", "south");
  set_noshow_obvious(1);
  add_prop(OBJ_S_WIZINFO,"@@wizinfo");
}

wizinfo()
{
  return ("Welcome to the Elvish starting place.\n"+
          "This place is known under the name Cuivienen, and is  well  known\n"+
          "to be the place of awakening of the Elvenrace.\n"+
          "Places to go from here: north - northern part of the beach\n"+
          "                        east  - forest\n"+
          "                        south - forest\n");
}

/*
 * Generic Elvish start.
 * Second room of the forest.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A forest");
  set_long(""+
   "You enter the forest to the south of the beach and take a  look  at  the\n"+
   "environment.  You see beautiful green trees  and  a  carpet  of  flowers\n"+
   "around you.  You hear some fine music far away.\n"+
   "A path is leading east.\n");
  add_item("path",
   "The path will lead you east in the forest.\n");
  add_item("forest",
   "The forest is much to dense to pass here.\n");
  add_exit(STANDARD_DIR + "start", "north");
  add_exit(STANDARD_DIR + "forest3", "east");
  set_noshow_obvious(1);
}

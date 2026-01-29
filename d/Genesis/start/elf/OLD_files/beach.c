/*
 * Generic Elvish start.
 * Northern part of the beach.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A beach");
  set_long(""+
   "You find yourself at the northern part of a beach, with a  path  leading\n"+
   "south to the rest of the beach.  Further to the north you  see  a  white\n"+
   "shape, which looks like a sail.  As your sight moves to the east you see\n"+
   "a mountain range in the distance, and to the east a forest  in  between.\n"+
   "It seems that the only possible directions in which you could travel are\n"+
   "to the north and south.\n");
  add_item("sea",
   "Never have you seen something like this.  This sea is so blue, that  you\n"+
   "can't imagine any other like this.\n");
  add_item(({"path", "paths"}),
   "Looking at the paths, you see that one is heading north, leading to what\n"+
   "might be a harbour.  To the south a path leads to the southern  part  of\n"+
   "this beach.\n");
  add_item("forest",
   "The forest is much to dense to pass here.\n");
  add_exit(STANDARD_DIR + "harbour1", "north");
  add_exit(STANDARD_DIR + "start", "south");
  set_noshow_obvious(1);
}

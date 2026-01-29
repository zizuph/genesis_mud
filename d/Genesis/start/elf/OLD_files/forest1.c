/*
 * Generic Elvish start.
 * First room of the forest.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A forest");
  set_long(""+
   "You pass through the natural portal and find yourself in a  rather  nice\n"+
   "forest.  The trees are green and a carpet of flowers is  stretching  out\n"+
   "under your feet.  The music you heard seems to come from a little  water\n"+
   "fall in the east part of this enterance of the forest.\n"+
   "A nice path is leading south from here.\n"+
   "In all other directions the forest is to dense to pass.\n");
  add_item("path",
   "The path will lead you south in the forest.\n");
  add_item("forest",
   "The forest is much to dense to pass here.\n");
  add_exit(STANDARD_DIR + "start", "west");
  add_exit(STANDARD_DIR + "forest3", "south");
  set_noshow_obvious(1);
}

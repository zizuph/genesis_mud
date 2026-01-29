/*
 * Generic Elvish start.
 * Third room of the forest.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A forest");
  set_long(""+
   "After some travel you find yourself far in this  forest.   Although  all\n"+
   "you see here is beautiful, you are longing for the sea.  That sea marked\n"+
   "itself in your memory.  Will you ever forget it?  You doubt it  and  are\n"+
   "longing to return to it.\n"+
   "Paths are leading west and north from here.\n");
  add_item("forest",
   "The forest is much to dense to pass here.\n");
  add_exit(STANDARD_DIR + "forest1", "north");
  add_exit(STANDARD_DIR + "forest2", "west");
  set_noshow_obvious(1);
}

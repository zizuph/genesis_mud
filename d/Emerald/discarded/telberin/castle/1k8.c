/*
 * 1k8.c
 * Library off of the sitting room in Castle Telberin
 * don't know who the original coder is.
 * Updated/Re-described by Alaron August 15,1996
 */
#include "default.h"

inherit CASTLE_ROOM; 

void
create_room()
{
    ::create_room();
   set_short("Library");
   set_long("   This is a modest, but impressive library. The small room "+
	    "is dimly lit with glass-covered lamps, basking the vast "+
	    "shelves of information in a flickering yellow and orange "+
	    "glow. In the center of the room rests a large, oak table. "+
	    "Along the west and east sides of the room are shelves "+
	    "filled to overflowing with books. In the northwest corner "+
	    "there is a ladder to help reach the texts on the higher "+
	    "shelves.\n\n");

   add_item( ({"lamps", "glass-covered lamps"}),
	    "They are small, but effective lamps. They give off enough "+
	    "light to make it easy to maneuver through the aisles of "+
	    "books in this small room.\n");
  
   add_item( ({"table", "oak table", "large oak table"}),
	    "It is a large, oak table. From the arrangement of papers "+
	    "and information on it, it looks like a research bench.\n");

   add_item( ({"shelves", "books"}),
	    "The shelves filling the room are overflowing with books.\n");


   add_item("ladder",
	    "The ladder is really nothing more than a stool with two "+
	    "large wooden grip handles, but it helps people reach "+
	    "the texts stacked on the top of the shelves.\n");

   add_exit(CASTLE_DIR + "1k4","north");
   add_exit(CASTLE_DIR + "1k7","south");
}





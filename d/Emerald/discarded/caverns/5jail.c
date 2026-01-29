/*
 * 5jail.c
 * This is the main hallway of the underground prison in the pirate caverns
 * - Alaron September 15, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
   object door;
   set_short("Main hallway");
   set_long("   This is an enormous hallway formed out of the damp, "+
	    "fungus-ridden rock which honeycombs all throughout the "+
	    "base of the volcano and the ocean floor. A horrible odor "+
	    "of death and decay drifts into the hallway from a cell "+
	    "to the east. The hallway continues on throughout the "+
	    "underground jail to the north and southwest.\n\n");

   add_item("hallway",
	    "The hallway continues throughout the underground jail "+
	    "to the north and southwest. There is a jail cell to "+
	    "the east.\n");

   add_item(({"cell","prison cell"}),
	    "The cell looks horrible. It appears to have been neglected "+
	    "for years. A foul, rank stench drifts up and out of the "+
	    "dark chamber. It is too dark to see any further details.\n");
   
   add_exit(THIS_DIR + "4jail", "east");
   add_exit(THIS_DIR + "6jail", "southwest");
   add_exit(THIS_DIR + "3jail","north");
   
   seteuid(geteuid());
   door = clone_object(THIS_DIR+"obj/pdoor4a");
   door ->move(TO);
}

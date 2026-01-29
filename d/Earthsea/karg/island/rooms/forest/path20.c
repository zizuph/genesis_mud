#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
 set_short("In green valley");
 set_long("Path continues runing through the green valley. Back to "+
   "south you can figure out high hills, while to north you start "+
   "to see clearly the massive siluette of the stronghold.\n");

 add_item(({"stronghold","fortress"}),
   "It is too far to see details, but it is huge!\n\n");
 add_item("valley","Green grassy valley can be seen from here. It is "+
   "located between high cliffs. Small path is running through "+
   "the valley.\n");
 add_item("cliffs","High cliffs surround the valley from all sides.\n");

 add_exit(FROOMS+"/path21","northeast");
 add_exit(FROOMS+"/path19","south");
}


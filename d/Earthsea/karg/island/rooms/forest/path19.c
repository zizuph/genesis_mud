#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
 set_short("Down the valley");
 set_long("Path descends from the hills, down to the green valley. "+
   "Back to southwest you see hills, while further to north you can "+
   "clearly see massive stronghold.\n");

 add_item(({"stronghold","fortress"}),
   "It is too far to see details, but it is huge!\n\n");
 add_item("valley","Green grassy valley can be seen from here. It is "+
   "located between high cliffs. Small path is running through "+
   "the valley.\n");
 add_item("cliffs","High cliffs surround the valley from all sides.\n");

 add_exit(FROOMS+"/path20","north");
 add_exit(FROOMS+"/path18","southwest");
}


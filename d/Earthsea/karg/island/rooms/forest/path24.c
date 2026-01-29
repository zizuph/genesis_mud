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
   "south you can figure out high hills. To the north stronghold "+
   "is starting to grow to really huge size. It's now blocking the "+
   "sun, and you suddenly find yourself in its shadow.\n");

 add_item(({"stronghold","fortress"}),
   "It's huge, really enormous. Your neck starts to ache when you "+
   "look upwards, trying to see it's top. On the top of stronghold "+
   "you see flag of Karg Empire flowing in the wind. Huge gate lead "+
   "into the fortress.\n");

 add_item("valley","Green grassy valley can be seen from here. It is "+
   "located between high cliffs. Small path is running through "+
   "the valley. Not far away to north you can see valley end, though "+
   "the path keeps running further amd connects with stronghold "+
   "bridge.\n");

 add_item("cliffs","High cliffs surround the valley from all sides.\n");

 add_exit(FROOMS+"/path25","north");
 add_exit(FROOMS+"/path23","south");
}


#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
 set_short("On the bridge");
 set_long("You are standing at the bridge over the moat, leading to "+
   "the stronghold. Back to south you can see the valley, while to "+
   "north you can see huge gates leading to the stronghold. "+
   "Stronghold itself is surrounded by high cliffs from all sides, "+
   "and only narrow passage leads southwards.\n");

 add_item(({"stronghold","fortress"}),
   "It's huge, really enormous. Your neck starts to ache when you "+
   "look upwards, trying to see it's top. On the top of stronghold "+
   "you see flag of Karg Empire flowing in the wind. Huge gate lead "+
   "into the fortress.\n");

 add_item("valley","Valley end can be see to the south.\n");

 add_item("cliffs","Stronghold is surrounded by high cliffs. They "+
   "look very steep. You doubt it is possible to climb those "+
   "cliffs.\n");

 add_item("bridge","It leads directly to the stronghold gates, over "+
   "the moat.\n");

 add_item("moat","It is filled with boiling water! You don't want to "+
   "think what happens if you fall down!\n");

 add_exit(FROOMS+"/bridge2","north");
 add_exit(FROOMS+"/path25","south");
}


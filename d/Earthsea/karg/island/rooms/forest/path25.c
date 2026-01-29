#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

int closed=0;

void
create_island_room()
{
 set_short("Valley end");
 set_long("High cliffs surround you from east, west and north. Small "+
   "path runs into the valley to your south. To the north you see "+
   "narrow passage between cliffs, leading directly to stronghold "+
   "bridge.\n");

 add_item(({"stronghold","fortress"}),
   "It's huge, really enormous. Your neck starts to ache when you "+
   "look upwards, trying to see it's top. On the top of stronghold "+
   "you see flag of Karg Empire flowing in the wind. Huge gate lead "+
   "into the fortress. Only now you realize the strategical advantage "+
   "of this location. Stronghold is surrounded by high cliffs, and "+
   "the only narrow passage can be easily defended by only several "+
   "guards.\n");

 add_item("valley","Valley seems to end here. Only small path leads "+
   "back to the valley towards south.\n");

 add_item("cliffs","High cliffs surround the valley from all sides.\n");

 add_item("bridge","@@bridge");

 add_exit(FROOMS+"/bridge1","north","@@block");
 add_exit(FROOMS+"/path24","south");
}

int block()
{
 if(!closed) return 0;

 write("The bridge is raised, disabling outsiders to enter the "+
   "stronghold.\n");
 return 1;
}

void close() 
{
 tell_room(TO,"Bridge slowly starts to raise.\n");
 closed=1;
}
void open() 
{
 tell_room(TO,"Bridge slowly starts to lower.\n");
 closed=0;
}

string bridge()
{
 string res="It leads directly to the stronghold gates, over "+
   "the moat. ";

 if(closed) return res+"Bridge is raised, disallowing to enter the "+
   "stronghold.\n";
 else return res+"Bridge is lowered, allowing you to approach the "+
   "main gate.\n";
}


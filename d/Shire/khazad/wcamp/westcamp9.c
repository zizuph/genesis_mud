inherit "/d/Shire/khazad/moria_room_westcamp";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("In a dim cavern");
  set_long("You stand in a small depression. Stalagmites "+
     "practically block any further passage here. The path "+
     "seems to come to an end here. A tower rises above "+
     "the stalagmites off a ways to the southwest. A single "+
     "well worn path leads away from here to the south.\n");
 
/*
  add_item(({ "ceiling", "roof" }),
  add_item(({ "walls", "wall" }),
  add_item(({ "ground", "floor" }),
  add_item(({ "stalactite", "stalactites" }),
  add_item(({ "stalagmite", "stalagmites" }),
  add_item(({ "bat", "bats" }),
  add_item("cavern",
  add_item("insect", "insects", "beetles", "scorpions" }),
  add_item(({ "path", "paths" }),
  add_item(({ "pillar", "pillars" }),
  add_item("tower",
                   
*/
  add_exit("/d/Shire/khazad/wcamp/westcamp7","south",0,1);
}

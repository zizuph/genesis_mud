inherit "/d/Shire/khazad/moria_room_westcamp";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("In a dim cavern");
  set_long("You stand at the edge of a vast cavern. Numerous "+
     "stalagmites tower around you, screening you from seeing "+
     "what lies beyond. The only thing you can make out is a "+
     "high tower of stone that rises above the stalagmites in "+
     "the east. A well worn path will take you north deeper into "+
     "the forest of stone while another heads off to the south.\n");
 
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
  add_exit("/d/Shire/khazad/wcamp/westcamp8","north",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp2","south",0,1);
}

inherit "/d/Shire/khazad/moria_room_westcamp";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("In a dim cavern");
  set_long("You stand in the midst of a forest of stalagmites. "+
     "The air in here is warm and carries with it the smell of "+
     "death and decay. You feel uneasy walking under the throngs of "+
     "large brown bats that hang effortlessly above you. "+
     "Off a ways to the north you see a large stone tower. A few well "+
     "worn paths lead away from here. One heads off to the east, "+
     "another to the west, and yet another to the south.\n");
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
  add_exit("/d/Shire/khazad/wcamp/westcamp2","west",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp4","east",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp1","south",0,1);
}

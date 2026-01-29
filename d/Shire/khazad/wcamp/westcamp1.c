inherit "/d/Shire/khazad/moria_room_westcamp";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("In a dim cavern");
  set_long("You stand at the edge of a vast cavern. Stalactites "+
     "stretch downwards and join stalagmites forming mighty pillars of "+
     "stone as far as your eye can see. The air in here is warm and "+
     "carries a foul stench along with it. Thousands upon thousands of "+
     "bats hang overhead, oblivious in their deep slumber. You make out "+
     "a few well worn paths leading deeper into the cavern. One leads "+
     "north between the two nearest natural pillars. The other two follow "+
     "along the edges of the cavern to the northwest and northeast. A "+
     "narrow staircase ascends through a rectangular opening in the "+
     "southern wall.\n");
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
  add_item(({ "stairs", "staircase", "stairway", "opening" }),
*/
  add_exit("/d/Shire/khazad/wcamp/westcamp3","north",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp2","northwest",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp4","northeast",0,1);
//add_exit("/d/Shire/khazad/west/wd8","up",0,5);
}

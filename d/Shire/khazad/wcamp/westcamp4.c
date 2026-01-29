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
     "bats hang overhead, oblivious in their deep slumber. Off to "+
     "the northwest you see a massive tower of stone. A few well "+
     "worn paths lead further into the cavern. Paths to the "+
     "north and southwest run along the edge of the cavern "+
     "while another heads off to the west towards the heart of "+
     "the cavern.\n");
 
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
  add_exit("/d/Shire/khazad/wcamp/westcamp7","north",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp3","west",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp1","southwest",0,1);
}

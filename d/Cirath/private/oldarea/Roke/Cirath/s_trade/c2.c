inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In a tunnel");
  
  set_long(break_string(
           "You're in a dark and wet tunnel leading through a mountain. "+
           "It's a claustrophobic place with pebbles on the ground which "+
           "makes it very slippery to walk on.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"mountain","mountains","ridge"}),"You're travelling under it.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone ore something have made it. It leads through the mountain.\n");
  add_item(({"pebble","pebbles"}),"The pebbles are made by the constant dripping "+
    "of water from the ceiling.\n");

  INSIDE;

  add_prop(ROOM_I_LIGHT, 0);

  add_exit(S_TRADE+"c1","east");
  add_exit(S_TRADE+"c3","west");

}

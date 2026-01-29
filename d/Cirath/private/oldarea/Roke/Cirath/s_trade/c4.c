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
           "You're at the west end of a tunnel. West, you can see the light "+
           "and east it proceeds further inside the mountain.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"mountain","mountains","ridge"}),"The tunnel leads through it.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone ore something have made it. It leads through the mountain.\n");

  INSIDE;

  add_prop(ROOM_I_LIGHT, 0);

  add_exit(S_TRADE+"c3","east");
  add_exit(S_TRADE+"gate","west");

}

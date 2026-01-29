inherit "/std/room";
#include "defs.h"

void
create_room()
{
   object door;
   set_short("A cave.");
   set_long(
      "This room is very dark. Even with the door open it "+
      "is hard to see anything.\n"
   );
   add_item(({"ground","floor"}),
      "The ground is not stone, it seems to have a hollow "+
      "sound to it. It sounds a bit like wood.\n"
   );
   add_item(({"wall","walls"}),
      "The walls seem warmer than cave walls should be. "+
      "They are also damp and very dark. In fact they "+
      "almost seem to absorb any light that enters the "+
      "room.\n"
   );
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT,0);
   add_exit(THIS_DIR+"cave2","north",0);
   seteuid(getuid());
   door = clone_object(PIRATES_DIR+"/obj/door_a");
   door->move(TO);
}

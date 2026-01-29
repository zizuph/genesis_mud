inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
void
create_room() {
   set_short("garanga!\n");
   set_long("You are swimming underwater.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int4","up");
   clone_object("/d/Rhovanion/common/dungeon1/gear/hand.c")
   ->move(TO);
}

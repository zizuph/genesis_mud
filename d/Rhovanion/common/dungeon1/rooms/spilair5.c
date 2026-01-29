inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("hee hee hee\n");
   set_long("This narrow passageway ends here, but an even narrower still shaft continues downward from this cavern of sorts.\n");
   add_item("shaft","The shaft is only large enough for one man at a time to enter.  Its walls are rough and chisel-like leading you to believe they should be easy to climb.\n");
   add_item(({"wall","walls"}),"The walls here are of dark stone and appear almost naturally chiseled by some unknown force.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair3","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair6","down");
}

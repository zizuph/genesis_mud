inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("blackness\n");
   set_long("You are now standing in a nearly circular cavern of almost natural appearance about twenty feet in diameter.  The stone here is the same as the rest of the passageways you've been traveling through, but the air here is filled with a sort of black dust like soot, and judging by the smell you conclude it is definitely not soot.  It is dry and dank here.\n");
   add_item(({"wall","walls"}),"The walls upon closer inspection reveal strange almost chisel like scars.  If this is really a natural cavern then it must truly be unique.\n");
   add_item("floor","The floor, as you scrutinize it, appears not smooth, but nearly smooth.  It is marked with the pocks of a thousand dents;  not ordinary dents, but more as if a thousand soldiers with pegs for feet had traversed its surface many times over.  You figure this is a truly unique `natural' cavern.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair6","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair8","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair9","south");
}

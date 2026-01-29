inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   set_short("shaft bottom");
   set_long("You now find yourself at the bottom of a vertical shaft " +
      "in what appears to be a perhaps natural cavern of sorts.  The walls " +
      "are of oddly hewn dark stone and the floor, of the same " +
      "stone, is rather smooth.\n");
   add_item(({"wall","walls"}),"The walls upon closer inspection reveal strange almost chisel like scars.  If this is really a natural cavern then it must truly be unique.\n");
   add_item("floor","The floor, as you scrutinize it, appears not smooth, but nearly smooth.  It is marked with the pocks of a thousand dents;  not ordinary dents, but more as if a thousand soldiers with pegs for feet had traversed its surface many times over.  You figure this is a truly unique `natural' cavern.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair4","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair5","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair2","up");
}

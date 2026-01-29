inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("yeah, right\n");
   set_long("This is a small cavern of sorts with walls, ceiling, and floor made of that same dark, oddly-chiseled stone.  A narrow shaft extends up into the ceiling, and your ears detect more of those queer chitonous tappings upon stone further down the passageway.\n");
   add_item("shaft","This shaft has rough, oddly-chiseled walls that allow for easy climbing.\n");
   add_item("ceiling","The ceiling has a shaft extending up through it.\n");
   add_item(({"wall","walls"}),"The walls upon closer inspection reveal strange almost chisel like scars.  If this is really a natural cavern then it must truly be unique.\n");
   add_item("floor","The floor, as you scrutinize it, appears not smooth, but nearly smooth.  It is marked with the pocks of a thousand dents;  not ordinary dents, but more as if a thousand soldiers with pegs for feet had traversed its surface many times over.  You figure this is a truly unique `natural' cavern.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair5","up");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair7","east");
}

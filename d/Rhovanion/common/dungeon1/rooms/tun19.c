inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("room\n");
   set_long("The passage takes another abrupt turn here, but " +
      "is still flooded with a foot of water which is getting " +
      "annoying to slosh through.  What strikes you as you " +
      "travel further down is the slight yet obvious sideways " +
      "slant of the tunnel signaling to you the danger that " +
      "trancing around down here could bring.  You might " +
      "want to turn back.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_item("stone", "The stone here is of a dark, dark almost " +
      "black color that is very dull in luster and reflects " +
      "little light.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int6","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun20","south");
}

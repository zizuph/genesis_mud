inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("home\n");
   set_long("You are making your way through this passageway " +
      "submerged under a foot of water and rather filthy.  The large, " +
      "stone blocks in the walls and ceiling are in a state of " +
      "serious disrepair making you question the safety of " +
      "wandering about here.  It reaks of decay and filth here.\n");
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
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun13","south");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int5","east");
}

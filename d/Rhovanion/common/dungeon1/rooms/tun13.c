inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Tunnel.\n");
   set_long("This is a long, dark tunnel with large, stone " +
      "blocks comprising the walls and ceiling and a flat slab of " +
      "stone for the floor.  It's a bit dirty here and the air is " +
      "dank and mildewy.  Just to the north a ways the passageway " +
      "slopes slightly downward submerging itself under a thin layer " +
      "of water getting progressively deeper further north.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun14","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun12","north");
}

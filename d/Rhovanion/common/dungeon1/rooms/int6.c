inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("yes\n");
   set_long("You have just entered a small circular intersection " +
      "approximately ten feet in diameter with large, curved, stone " +
      "blocks comprising the walls and a ceiling arching high above " +
      "you in the dark depths over you.  The room is flooded with " +
      "about a foot of water and reaks of festering decay.\n" +
      "A short flight of stairs climb up out of the water off a ways " +
      "to the south and you hear scurrying noises just to your " +
      "north.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_item("ceiling", "The ceiling extends upward at least twenty " +
      "feet where stones jut out from it in an asthetically " +
      "pleasing pattern offering perches perhaps for creatures " +
      "able to cling to walls.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/trap2","steps");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun23","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun19","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun17","west");
}

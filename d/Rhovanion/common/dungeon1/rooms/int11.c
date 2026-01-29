inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("int\n");
   set_long("You've come across a large, circular room " +
      "approximately twenty feet in diameter with a vaulted ceiling " +
      "arching high into the dark depths above you. " +
      "The floor here is geometrically arranged with large, curved stone " +
      "blocks similar to those in the walls but arranged in a " +
      "circle around an oddly shaped center stone.  A large " +
      "door stands in the north wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("door","It is a slightly oversized door made of some solid " +
      "sturdy wood.  The door's been covered with finish so much " +
      "that you cannot determine the type of wood it is made " +
      "from under the dark, dark stain.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("center stone", "This stone is smooth, more polished " +
      "than the rest a bit, and expertly set into the floor perfectly " +
      "level obviously by a truly skillfull master craftsman.\n");
   add_item("ceiling", "The ceiling extends upward at least " +
      "twenty feet where stones jut out from it in an asthetically " +
      "pleasing pattern offering perches perhaps for creatures able " +
      "to cling to walls.\n");
   add_my_desc("The door is closed.\n");
   add_cmd_item("door","open","@@false_door");
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun32","south");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/alcove1","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/alcove2","east");
}
int
false_door() {
   say(QCTNAME(TP) + " tries to open the door to no avail.\n");
   write("You try to pry open the door, but it won't budge. " +
      "Perhaps you aren't strong enough. Perhaps it's something " +
      "else.\n");
   return 1;
}

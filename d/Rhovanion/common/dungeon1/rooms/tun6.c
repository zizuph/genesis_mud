inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("ransack!\n");
   set_long("The air in this passageway seems dryer and dustier than the others." +
      "You notice a film of some sort of dirt or dust layered upon the " +
      "floor.  Aside from that this passage is identical to the rest you've been " +
      "in only it doesn't feel that way.  It feels...  you feel... wary.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to be " +
      "nearly identical so you figure they must have been worked by " +
      "a master stoneworker.\n");
   add_item("stone", "The stone here is of a dark, dark almost black " +
      "that is very dull in luster and reflects little light.\n");
   add_item(({"film","dust","dirt"}),"This film is not really dust, but a fine dirt!\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int2","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/room1","south");
}

inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Mute made this.\n");
   set_long("The walls in this tunnel area a bit less dusty than the " +
      "rest of the large, stone blocked passageways here.  The " +
      "air, though fresher, bears an odd, scaly odour unfamiliar " +
      "to you.  Further west down the passage you think you see " +
      "the warm glow of a fire.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are lage, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard2","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int12","east");
}

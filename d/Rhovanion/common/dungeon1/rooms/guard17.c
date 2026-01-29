inherit "/std/room.c";
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute!\n");
   set_long("This is a small room approximately fifteen " +
      "feet square in size with large, stone blocks for the " +
      "walls and ceiling and a solid stone floor. A " +
      "well-made straw tatami mat lies against the west wall. " +
      "It smells oddly rank in here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item(({"mat","mats"}),"These are mats of long straws tied " +
      "together with strings horizontally.  You could use " +
      "one to sleep on if you were desperate.\n");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door6a.c")
   ->move(TO);
}

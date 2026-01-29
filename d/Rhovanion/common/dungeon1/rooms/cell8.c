inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
void
create_room() {
   set_short("Mutacious.\n");
   set_long("You now find yourself in a small stone " +
      "blocked room about fifteen square feet in size. " +
      "There is a stone arch set into the west wall where " +
      "a small, dark tunnel can be seen and there is, also, " +
      "a small passageway leading out to the east from where " +
      "a horrendous odour of decay emanates.\n" +
      "   A scratched, well-worn old desk sits in the north of " +
      "the room by the east passageway along with an old, worn " +
      "wooden chair.  You think you see a slight mist in here " +
      "and the air is stale and cold.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell7","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell17","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell4","south");
   clone_object("/d/Rhovanion/common/dungeon1/living/jailor.c")
   ->move(TO);
}

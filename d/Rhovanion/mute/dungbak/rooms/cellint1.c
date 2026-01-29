inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("int\n");
   set_long("This is an intersection in the passageway splitting off in all the
" +
      "cardinal directions.  The ceiling arches quite high above you and " +
      "dust covers the old, dilapidated stone blocks of the walls. " +
      "This place looks pretty shabby.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/bats.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/cell16","west");
   add_exit("/d/Rhovanion/mute/dungeon1/cell5","north");
   add_exit("/d/Rhovanion/mute/dungeon1/cell2","east");
   add_exit("/d/Rhovanion/mute/dungeon1/cell1","south");
}

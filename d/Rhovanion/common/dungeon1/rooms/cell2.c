inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("A whoppin good time!\n");
   set_long("The passageway turns north here.  Dust " +
      "covers the old, dilapidated stone blocks of the walls, " +
      "and there is a scent of decay in the air.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door11.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/cellint1","west");
   add_exit("/d/Rhovanion/mute/dungeon1/cell3","north");
}

inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute.\n");
   set_long("The tunnel makes a sharp turn here.  This " +
      "particular section of the tunnel is rather featureless " +
      "save for the layer of dust covering the old, shabby " +
      "stone blocks of the walls.  It's a bit chilly here and " +
      "there is an odd stale odour in the air.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell8","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell6","south");
}

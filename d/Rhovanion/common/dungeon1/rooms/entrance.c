/* Mute  Jan. 31, 1995 */
inherit "/std/room.c";

#include "/d/Rhovanion/defs.h"

void
create_room()
{
   set_short("Entrance");
   set_long("You now find yourself standing at the beginning of a " +
      "long, dark passageway.  The passageway appears to be man made as its " +
      "walls and ceiling are constructed of large, stone blocks, but " +
      "not the floor.  For the floor is solid, relatively smooth stone upon " +
      "which your footsteps echo and rebound down giving you a false " +
      "impression of where the sound originates from.  The air " +
      "here is dank, cold, and slightly stale.\n");
   add_prop(ROOM_I_INSIDE, 1);
   
   add_item("stone", "The stone here is of a dark, dark almost black color that is very dull in luster and reflects little light.\n");
   add_item("block", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_item("blocks", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun1","north");
}

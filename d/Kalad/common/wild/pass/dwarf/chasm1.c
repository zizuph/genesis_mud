inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Korat */

create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Path");
   set_long("You are hanging on to a small path in the mere wall of a "+
      "cliffside. Along you, there grows just a few scrubs "+
      "but further downwards you see a small shelf with "+
      "even a larger bush growing on it. The view here is "+
      "marvellous.\n");
   add_item(({"vegetation","scrubs","bush"}),"The shrubs cling "+
      "for their lives on the chasms wall, while that larger "+
      "bush seems to have better conditions for life.\n");
   add_item(({"cliffside"}),"An enormous cliffside, completely "+
      "prevents passage westward. The wall stretches far to the north and "+
      "south, into the horizon. Straining your eyes you believe you can make "+
      "out the western bottomside, which seems to be covered in forests.\n");
   add_item(({"forests","forest"}),"It appears as a green ocean.\n");
   add_item(({"great hespyre mountains","hespyre mountains","mountains","mountain"}),
      "They tower far above the surrounding landscape, dwarfing "+
      "everything in the land with their size and splendor. So great is "+
      "their height that they seem to block out the sky itself.\n");
   add_exit("/d/Kalad/common/wild/pass/w21","up",0,3,1);
   add_exit("/d/Kalad/common/wild/pass/dwarf/chasm2","down",0,3,1);
}

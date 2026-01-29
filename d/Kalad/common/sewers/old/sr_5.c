#include "/d/Kalad/defs.h"
inherit SEWERS(sewer_std.c);

void
create_room()
{
   ::create_room();
   set_short("A dim tunnel");
   set_long("You are standing in a dim tunnel beneath the city of "+
   "Kabal. The foul smelling sludge flows through the center of the "+
   "tunnel, producing a sick slurping sound. The walls here are made "+
   "of red brick, held together by some sort of crumbly mortar.\n");
   add_item("walls","Filthy, slime-covered brick.\n");
   add_exit("/d/Kalad/common/sewers/sr_2.c","southeast",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_6.c","east",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_15.c","nothwest",0,1,3);
}

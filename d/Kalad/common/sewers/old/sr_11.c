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
   add_item("walls","Filthy, slime-covered brick. You see light to "+
   "the west.\n");
   add_exit("/d/Kalad/common/sewers/sr_17.c","northwest",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_10.c","west",0,1,3);
   add_exit("/d/Kalad/common/sewers/tr_1.c","southwest",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_18.c","notheast",0,1,3);
}

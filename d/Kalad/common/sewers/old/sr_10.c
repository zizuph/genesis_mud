#include "/d/Kalad/defs.h"
inherit SEWERS(sewer_std.c);

void
create_room()
{
   ::create_room();
   set_short("A somewhat bright brick room");
   set_long("You are standing in a dim chamber beneath the city of "+
   "Kabal. The foul smelling sludge on the floor here, comes up to "+ 
   "your boots leaving dark collored streaks of filth on them. The "+ 
   "walls here are made of red brick, held together by some sort of "+
   "crumbly mortar. This is truly a dismal place indeed, the smell "+ 
   "alone is enough to make you want to run back to the surface. The "+
   "floor here is a swirling mass of filth. The light from the sky "+
   "floods in through the grate leading to the city above.\n");
   add_item("walls","Filthy, slime-covered brick.\n");
   add_exit("/d/Kalad/common/sewers/sr_8.c","west",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_11.c","east",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_9.c","south",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_17.c","north",0,1,3);
}

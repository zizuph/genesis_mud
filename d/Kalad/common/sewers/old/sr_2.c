#include "/d/Kalad/defs.h"
inherit SEWERS(sewer_std.c);

void
create_room()
{
   ::create_room();
   set_short("A damp and reeking brick room");
   set_long("You are standing in a dim chamber beneath the city of "+
   "Kabal. The foul smelling sludge on the floor here, comes up to "+ 
   "your boots leaving dark collored streaks of filth on them. The "+ 
   "walls here are made of red brick, held together by some sort of "+
   "crumbly mortar. This is truly a dismal place indeed, the smell "+ 
   "alone is enough to make you want to run back to the surface. You "+
   "notice some red eyes watching you from the darkness.\n");
   add_item("walls","Filthy, slime-covered brick.\n");
   add_item(({"eyes","red eyes"}),"They belong to the rats that"+
   " infest this disgusting place.\n");
   add_exit("/d/Kalad/common/sewers/sr_1.c","southeast",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_3.c","east",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_7.c","north",0,1,3);
   add_exit("/d/Kalad/common/sewers/sr_5.c","northwest",0,1,3);
}

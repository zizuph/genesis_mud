/* 
Citadel, kitchen.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Citadel, kitchen");
   set_long("This is the kitchen that prepares the food for all the "+
      "guards that belongs to the Citadel. Several cooks and servants "+
      "works hard on preparing the food that is needed at all times of "+
      "the day, all the days in the week, and year after year.\n");

   add_exit(CENTRAL(citadel/cit14),"southwest",0,-1,-1);
}

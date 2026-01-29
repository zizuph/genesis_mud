#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
 
void
create_er_room()
{
   area = "somewhere in";
   areaname = "East Farthing";
   land = "Eriador";
   areatype = 10;
   areadesc = "rolling hills";
   grass = "green";
 
   extraline = "The road runs east and west, through the hills of the " +
   "East Farthing. Bushes dot the land and grow alongside the road. " +
   "Slim hills stand in the distance.";
 
   add_item(({"bush","bushes"}),"The bushes are lush and green, full "+
   "of health and life.\n");
   add_item("landscape","All around you is green, growing and "+
   "vibrant.\n");
   add_item(({"brown road","road"}),"The road is brown from "+
   "mud having overtaken the grey pebbles and cobblestones in "+
   "places.\n");
   add_item(({"hill","hills","slim hill","slim hills"}),
   "The hills nearby are slight and rolling, very pleasant all in all.\n");
  
   add_exit(EAST_R_DIR + "er21","west",0,2);
   add_exit(EAST_R_DIR + "er21b","east",0,2);
}
 

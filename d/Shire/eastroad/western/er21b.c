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
 
   extraline = "Rolling hills rise in the distance. They are rounded " +
   "and covered with bushes. The road runs past them, and cuts its " +
   "way through meadows here.";  
 
   add_item(({"bush","bushes"}),"The bushes are lush and green, full "+
   "of health and life.\n");
   add_item("landscape","All around you is green, growing and "+
   "vibrant.\n");
   add_item(({"brown road","road"}),"The road is brown from "+
   "mud having overtaken the grey pebbles and cobblestones in "+
   "places.\n");
   add_item(({"hill","hills","slim hill","slim hills"}),
   "The hills nearby are slight and rolling, very pleasant all in all.\n");
   add_item(({"meadows"}),
       "They are green and thick, and cover the land.\n");
  
   add_exit(EAST_R_DIR + "er21a","west",0,2);
   add_exit(EAST_R_DIR + "er21c","east",0,2);
}
 

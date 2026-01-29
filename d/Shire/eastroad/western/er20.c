#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
 
void
create_er_room()
{
   area = "just east of";
   areaname = "Frogmorton";
   land = "Eriador";
   areatype = 10;
   areadesc = "rolling hills";
   grass = "green";
 
   extraline = "The bushes that dot the landscape "+
   "around the road are lush, home to many kinds of life. The brown "+
   "road winds through the slim hills here, turning to meet the "+
   "Baranduin river at a right angle.";
 
   add_item(({"bush","bushes"}),"The bushes are lush and green, full "+
   "of health and life.\n");
   add_item("landscape","All around you is green, growing and "+
   "vibrant.\n");
   add_item(({"brown road","road"}),"The road is brown from "+
   "mud having overtaken the grey pebbles and cobblestones in "+
   "places.\n");
   add_item(({"hill","hills","slim hill","slim hills"}),
   "The hills nearby are slight and rolling, very pleasant all in all.\n");
   add_item(({"river","baranduin river","brandywine river","baranduin","brandywine"}),
   "The Baranduin, or Brandywine river murmurs quietly as it "+
   "makes its brown and muddy way south, towards Sarn Ford and "+
   "later, the Sea.\n");
   add_item("angle","The angle the road will meet the river is "+
   "nearly perpendicular.\n");

   add_exit(EAST_R_DIR + "er19","west",0,2);
   add_exit(EAST_R_DIR + "er21","east",0,2);
}
 

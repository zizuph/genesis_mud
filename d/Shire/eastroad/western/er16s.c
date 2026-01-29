#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "some distance from";
   areaname = "Frogmorton";
   land = "the Shire";
   areatype = 1;
   areadesc = "field";
   grass = "green";
   
   extraline = "This is typical of the fields that dominate this "+
   "part of Shire. North is the Great Eastroad, beyond which is "+
   "the stream known as The Water, a tributary of the Brandywine "+
   "River. Very far to the south is Tookland, however it cannot "+
   "be seen from here.";
   
   
   add_item(({"water","the water","stream"}),
      "   Just off to the north, the small stream runs off to the east, "+
      "where it will eventually merge togeather with the great river "+
      "Baraduin.\n");
   add_item(({"surroundings","expanse","fields","shire"}),
      "   The fields of the Shire stretch out in all directions. To "+
      "the north, Eastroad can be seen as a thin brown strip, weaving "+
      "through the fields.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er16","north",0,2);
   add_exit(EAST_R_DIR + "er17","east",0,2);
   add_exit(EAST_R_DIR + "er15s","west",0,2);
   
}

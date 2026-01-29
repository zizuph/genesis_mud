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

   extraline = "You find yourself in the grassy fields that seem to "+
      "dominate the Shire. Off to the north, the small stream the "+
      "Hobbits call 'The Water' runs merrily around the hills, and "+
      "to the south, a narrow brown strip marks the running of the "+
      "great Eastroad. Far off to the east, the small village of "+
   "Frogmorton rests on the Eastroad; while to the west, the gentle "+
      "village of Bywater lies nestled upon the banks of 'The Water'.";

   add_item(({"water","the water","stream"}),
   "   Just off to the north, the small stream runs off to the east, "+
   "where it will eventually merge togeather with the great river "+
   "Baraduin.\n");
   add_item(({"surroundings","expanse","fields","shire"}),
   "   The fields of the Shire stretch out in all directions. To "+
   "the north a narrow blue ribbon is all you can see of a small stream, "+
   "while to the south, a thin brown strip marks the Eastroad as it passes "+
   "by.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er15","south",0,2);
   add_exit(EAST_R_DIR + "er16n","east",0,2);
   add_exit(EAST_R_DIR + "er14n","west",0,2);
   
}

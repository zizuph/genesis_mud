#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;


#define EXIT2 EVENDIM_DIR + "ev1","north",0,2
#define EXIT3 ER_DIR + "er17n3","east",0,2


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
   "dominate the Shire. There is a road here that seems to span "+
   "The Water and lead further north, towards, what "+
   "seem to be campfires. The noise from the north causes you to "+
   "be wary of going there.";
   
   
   add_item(({"water","the water","stream"}),
      "   Blocking passage to the north, the small stream runs off to "+
      "the east, "+
      "where it will eventually merge togeather with the great river "+
      "Baraduin.\n");
   add_item(({"surroundings","expanse","fields","shire"}),
      "   The fields of the Shire stretch all around you, flailing out "+
      "in all directions. To the north, a small stream is visible, "+
      "while to the south, a narrow brown strip of road passes by.\n");

   set_noshow_obvious(1);
   add_exit(EVEN_DIM_DIR + "ev1","north",0,2);
   add_exit(EAST_R_DIR + "er16n","south",0,2);
   add_exit(EAST_R_DIR + "er17n3","east",0,2);
   
}

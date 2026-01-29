#pragma save_binary
#pragma strict_types
 
#include "local.h"
 
inherit EAST_ROAD;
 
void
create_er_room()
{
   area = "passing through";
   areaname = "Frogmorton";
   land = "the Shire";
   areatype = 10;
   areadesc = "village";
   grass = "green";
 
   extraline = "Frogmorton is the halfway point between the village "+
   "of Bywater, to the west and Buckland, to the east. The village "+
   "proper lies north of Eastroad. The northern end of "+
   "Frogmorton borders The Water, a tributary of the Brandywine "+
   "river. While to the south, far from the village, the woods "+
   "and hills of Green Hill Country can be seen, however, "+
   "there seems to be no way of reaching them from here.";

   add_item ("Frogmorton", "This small Hobbit Village spreads out "+ 
      "north, on a narrow plain between Eastroad and The Water.\n");
   
   add_item(({"bywater"}),"The village of Bywater is just off to the "+
      "west, past the Three Farthing Stone. Set on the junction "+
      "of the East Road and the road to Hobbiton, Bywater still "+
      "maintains the appearance of a peaceful Hobbit village.\n");
 
   add_item(({"water","the water","river"}),"At this distance "+
      "The Water only appears as a thin, narrow river, running "+    
      "across the gentle rolling hills of the Shire.\n");
      
   add_exit("/d/Shire/frogmorton/road01","north",0,2);
   add_exit(EAST_R_DIR + "er18","southwest",0,2);
   add_exit(EAST_R_DIR + "er20","east",0,2);
}

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
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "You are standing on the East Road, somewhere between "+
"Frogmorton and Bywater in the East Farthing. Just in sight to the north, "+
   "you can spot a thin "+
   "ribbon of water winding its way across the plains. It looks to be the "+
   "stream the Hobbits call 'The Water', the small tributary of the great river "+
    "Baranduin that passes through the Shire. The road runs southeast "+
   "and west from here.";
   add_item(({"frogmorton"}),"   The small Hobbit village of Frogmorton lies "+
      "over ten miles distant in the east. From here, it seems to be no more than "+
      "a smudge on the horizon where the East Road and The Water almost touch "+
      "together.\n");
   add_item(({"bywater"}),"The Hobbit village of Bywater is just off to the "+
      "west, past the Three Farthing Stone. Set on the junction of the East Road "+
      "and the road to Hobbiton, Bywater still maintains the appearance of a "+
      "peaceful Hobbit village.\n");
   
   add_item(({"water","the water","baraduin","river"}),"At this distance, "+
      "'The Water' only appears as a thin, narrow river, running across the "+
      "gentle hills of the Shire.\n");
 
   add_exit(EAST_R_DIR + "er15","west",0,2);
   add_exit(EAST_R_DIR + "er17","southeast",0,2);
   add_exit(EAST_R_DIR + "er16s","south",0,2,1);
   add_exit(EAST_R_DIR + "er16n","north",0,2,1);
   add_exit(EAST_R_DIR + "er17n","east",0,2,1);
  
}

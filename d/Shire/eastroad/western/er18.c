#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "close to";
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
   "Baranduin that passes through the Shire. Also branching off to "+
   "the north here is a narrow, dirt path that heads off towards "+
   "Oatbarton in the North Farthing. The road runs northeast and "+
   "southwest from here.";
   add_item(({"frogmorton"}),"   The small Hobbit village of Frogmorton lies "+
      "only about five miles distant in the east. From here, the village "+
      "seems to sprawl out on a narrow plain where the East "+
      "Road and the Water seem to touch togeather.\n");
   add_item(({"bywater"}),"The Hobbit village of Bywater is just off to the "+
      "west, past the Three Farthing Stone. Set on the junction of the East Road "+
      "and the road to Hobbiton, Bywater still maintains the appearance of a "+
      "peaceful Hobbit village. You would judge that it lies almost "+
      "fifteen miles off to the west.\n");
   
   add_item(({"water","the water","baraduin","river"}),"At this distance, "+
      "'The Water' only appears as a thin, narrow river, running across the "+
      "gentle hills of the Shire.\n");
   add_item(({"path","oatbarton"}),"A narrow, dirt path seems to "+
      "off from the East Road here, running across the Water to the "+
      "north, towards the Hobbit town of Oatbarton in the North "+
      "Farthing.\n");

   add_exit(EAST_R_DIR + "er17","southwest",0,2);
   add_exit(EAST_R_DIR + "er19","northeast",0,2);
   add_exit(EAST_R_DIR + "er18n","north",0,2);
   add_exit(EAST_R_DIR + "er17n","west",0,2,1);
}

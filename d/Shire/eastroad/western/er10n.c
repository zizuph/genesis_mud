#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "some distance from"; /* Distance from areaname */
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 1;
   areadesc = "rolling plain";
   grass = "long";
   
   extraline = "This plain, running parallel to the Great East Road to "
   +"the south, extends far to the north and consists of little but "
   +"a sea of grass, with only an occasional bush or rock to break "
   +"the monotony.";
   
   add_item(({"village","michel delving"}),
      "Far to the west of here, the village of Michel Delving can barely "
      +"be seen.  The roofs of the larger houses are all that are visible "
      +"at this distance.\n");
   
   add_item(({"bush","bushes","rock","rocks"}),
      "Scattered over the plain are little bushes that are flourishing "
      +"on the rich soil of the Shire, and rocks broken from boulders "
      +"long ago.\n");
   
   add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
   
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er10","south",0,2);
   add_exit(EAST_R_DIR + "er11n","east",0,3);
   add_exit(EAST_R_DIR + "er9n","west",0,3);
   
}

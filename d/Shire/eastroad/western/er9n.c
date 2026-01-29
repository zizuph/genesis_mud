#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "not far from"; /* Distance from areaname */
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 4;
   areadesc = "field of wheat";
   grass = "freshly cut";
   
   extraline = "A few miles east of the village of Michel Delving, "
   +"this field and others like it supply the grain and wheat for "
   +"the village. These fields stretch far off to the north and east, "
   +"while the Great East Road lies to the south. Here and there, "
   +"amongst the fields, you can see animal tracks.";
   
   add_item(({"village","michel delving"}),
      "Lying to the west and southwest of the fields, the village of "
      +"Michel Delving sprawls out, with its farms and houses and "
      +"its fine inn.\n");
   
   add_item(({"tracks","track","animal","animal tracks"}),
      "You see many tracks across the fields here-some rabbits you "
      +"think, or maybe even the prints of a deer or something larger.\n");
   
   add_item(({"surroundings","expanse","fields","shire"}),
      "The fields stretch off into the distance, supplying food to "
      +"the surroundings villages and hamlets. "
      +"In the middle of the fields to the south runs the Great East "
      +"Road, a brown strip against the expanse of gold and green.\n");
   
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er9","south");
   add_exit(EAST_R_DIR + "er10n","east");
}

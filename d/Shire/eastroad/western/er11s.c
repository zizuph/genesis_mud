#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "close to"; /* Distance from areaname */
   areaname = "Waymeet";
   land = "the Shire";
   areatype = 1;
   areadesc = "hill";
   grass = "green";

   extraline = "This hill rises slightly from the surrounding plains, "
	+"giving a good view of the area. To the north is the Great "
	+"East Road, while smaller roads split off from the Great "
	+"East Road to the west and east of here. The hamlet of "
	+"Waymeet lies just over the hill to the northeast, situated "
	+"around the cross-road that gives it its name.";
   
   add_item(({"hamlet of waymeet","hamlet","waymeet"}),
   	"This small hamlet is a cluster of houses surrounding "
   	+"a cross-road. You can see an inn there as well.\n");

   add_item(({"surroundings","expanse","plains","shire","area"}),
   	"The plains stretch out of sight in all directions, only "
   	+"occasionally broken by roads or little clusters of houses.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er11","north",0,2);
   add_exit(EAST_R_DIR + "er10s","west",0,2);
   add_exit("/d/Shire/waymeet/rooms/streets/street_8","east",0,2);

}

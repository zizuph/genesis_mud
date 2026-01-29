#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;


void
create_er_room()
{
   area = "outside of";
   areaname = "Greenholm";
   land = "Eriador";
   areatype = 1;
   areadesc = "meadow";
   grass = "green";

   extraline = "The flat green meadows of Eriador stretch "+
   "before your eyes in all directions.  The Bounds of the Shire "+
   "lie to the east; western Eriador and Mithlond are west.";

   add_item(({"meadow","meadows","flat green meadows"}),
   "The green meadows are rich in vegetation and herb-life.\n");

   add_item(({"bounds","bounds of the Shire"}),
   "The Bounds of the Shire are to the east, given "+
   "to the hobbits of the Shire by King Argeleb II of "+
   "Arnor, when the Dunedain still ruled the North.\n");

   add_item(({"eriador","mithlond"}),
   "Eriador surrounds the Shire, which is technically a part of "+
   "it, just as Eriador is a part of Arnor, the former north Kingdom "+
   "of Middle Earth.  Mithlond, where Cirdan keeps his fleet, is "+
   "also part of Eriador, and also known as Grey Havens.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er5","south");
   add_exit(EAST_R_DIR + "er4n","west");
   add_exit(EAST_R_DIR + "er6n","east");
}

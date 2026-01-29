#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "near"; /* Distance from areaname */
   areaname = "Hobbiton";
   land = "the Shire";
   areatype = 1;
   areadesc = "hill";
   grass = "green";
   
   extraline = "The village of Hobbiton is visible north of "+
   "the Great East Road at this point, past the fields that line "+
   "the road. To the east and west there are paths through "+
   "the rolling hills. North the Great East Road stretches "+
   "a great distance from Mithlond in the west to Rivendell in the east. ";
   
   
   add_item(({"field","fields"}),"Fields line the road, providing "+
      "valuable crops for the inhabitants of the Shire.\n"); 
   
   add_item(({"hobbiton","village"}),
      "Faintly visible over the fields to the north is the village of "+
      "Hobbiton, the former capital of the  Shire.  It doesn't look "+
      "like you can get to Hobbiton over the fields though, "+
      "you will have to take one of the roads there.\n");
   
   add_item(({"green hill country","hill","took hills"}),
      "The Green Hill Country is home to the Tooks, one of the great "+
      "families of the Shire.\n");
   
   add_item("bree","Far to the east is Bree, one of the larger "+
      "villages in the Shire, home to many strange people.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er13","north",0,2);
   add_exit(EAST_R_DIR + "er14s","east",0,2);
   add_exit("/d/Shire/waymeet/rooms/streets/street_8","west",0,2);
}

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "near";
   areaname = "Undertowers";
   land = "Eriador";
   areatype = 1;
   areadesc = "field";
   grass = "green";

   extraline = "This small field is hemmed in to the south and southwest "+
   "by a thick jungle of briars.  The East Road takes a bend to the south as "+
   "you can see the road directly to your east, south of the road is another field. "+
   "To the west there is also another field, leading back towards the village "+
   "of Undertowers.  North is the Great East Road leading from Mithlond to "+
   "Bree.";

   add_item(({"field","another field","west field","southeast field"}),
   "All around you is flat open field-land, other than the thick bungle of "+
   "briars to the south.\n");

   add_item(({"jungle","thick jungle","briars","thick jungle of briars"}),
   "This thick jungle of briars looks thick enough to keep even the rabbits "+
   "out. It is impenetrable, and you keep a good distance, hoping not to be "+
   "stuck on the very sharp and tangling briars.\n");

   add_item(({"undertowers","village"}),"The village of Undertowers lies to "+
   "the west.\n");

   add_item(({"east road","great east road",}),
   "The Great East Road leads from Mithlond in the west to Bree in "+
   "the east.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er4","north");
   add_exit(EAST_R_DIR + "er5s","east");
   add_exit(EAST_R_DIR + "er3s","west","@@leave_shire@@");
}


void leave_shire()
{
    write("You cross the West Farthing border and leave the Shire.\n");
}
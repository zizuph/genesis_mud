#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "not far"; /* Distance from areaname */
   areaname = "Westmarch";
   land = "Eriador";
   areatype = 10;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "The village of Undertowers is just to the west as "+
   "the Three Elven Towers rise over the horizon. Some small hobbit-holes "+
   "are to be found, but in general not many hobbits live outside the Shire. "+
   "The Far Downs curve the horizon to the east, and it is possible to go "+
   "north or south into the meadows surrounding the East Road.";

   add_item(({"meadow","meadows"}),"The meadows to the north and south "+
   "look wholesome and refreshing.\n");

   add_item(({"undertowers","westmarch","village"}),
   "The village of Undertowers in Westmarch is a tiny one indeed, "+
   "not surprising, considering it lies outside the boundaries of the "+
   "Shire.\n");

   add_item(({"hills","hill","rolling hills","tower hills","far downs"}),
   "This area is made of hills, hills and more hills. The Far Downs "+
   "wrinkle the surface of the earth to the east, as the Tower Hills "+
   "do so in the west. In between are these hills, which make "+
   "up a great deal of Westmarch.\n");

   add_item(({"hobbit holes","hobbit-holes","holes"}),
   "The hobbit holes around here are dug right into the "+
   "sides of the hills, a convenient arrangement to be sure. "+
   "They look reasonably big and not too crowded, though "+
   "it seems impossible to enter them.\n");

   add_exit(EAST_R_DIR + "er3","west", "@@leave_shire@@");
   add_exit(EAST_R_DIR + "er5","east");
   add_exit(EAST_R_DIR + "er4n","north",0,2,1);
   add_exit(EAST_R_DIR + "er4s","south",0,2,1);
}

void leave_shire()
{
    write("You cross the West Farthing border and leave the Shire.\n");
}
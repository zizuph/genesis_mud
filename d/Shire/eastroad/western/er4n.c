#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "not far from";
   areaname = "Undertowers";
   land = "Eriador";
   areatype = 1;
   areadesc = "meadow";
   grass = "green";

   extraline = "Above and to the west are the Elven Towers, where "+
   "elvish magic is rumored to be at work.  Holding the Three Towers "+
   "up are the Tower Hills, off in the distance.  To the east are the Far "+
   "Downs, and all around you the fields of "+land+" stretch out in "+
   "tranquil beauty.";

   add_item(({"elven towers","elvish magic","three towers","tower hills"}),
   "The Three Elven Towers were built long ago and it is believed they "+
   "are a center of magical knowledge, having been built by magic and "+
   "maintained by magic.\n");

   add_item(({"far downs","far down"}),"The bumps on the eastern "+
   "horizon are what must be the Far Downs, where the village of "+
   "Greenholm is situated.\n");


   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er4","south");
   add_exit(EAST_R_DIR + "er3n","west","@@leave_shire@@");
   add_exit(EAST_R_DIR + "er5n","east");
}


void leave_shire()
{
    write("You cross the West Farthing border and leave the Shire.\n");
}
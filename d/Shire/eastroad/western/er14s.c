#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "not far from"; /* Distance from areaname */
   areaname = "Hobbiton";
   land = "the Shire";
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "This is the beginning of a road that will eventually "+
   "lead through the Green Hill Country, to the region "+
   "known as Tookland. The road is currently under construction, "+
   "making it too dangerous to use.";
      
   add_item(({"hobbiton","village"}),
      "Northwest lies the village of Hobbiton, home of Bag End."+
      "A stream, known as The Water, runs through the middle of "+
      "Hobbiton, on its way to the Brandywine River to the East.  "+
      "Hobbiton is the pride of the Shire, with much to offer "+
      "to weary travellers.\n");
   
   add_item(({"tookland","green hill country"}),
      "The Took Hills to the south are the homeplace for the Tooks, "+
      "one of the great families of hobbits.  These hills have produced "+
      "many a leader of the Shire.\n");

   add_exit(EAST_R_DIR + "er13s","west",0,2,1);
   add_exit(EAST_R_DIR + "er15s","east",0,2);
   add_exit(EAST_R_DIR + "er14","north",0,2);
   add_exit(EAST_R_DIR + "lpath1","southeast",0,1);
}

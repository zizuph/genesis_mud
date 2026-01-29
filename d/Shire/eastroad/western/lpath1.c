#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{   
   area = "a bit south of"; /* Distance from areaname */
   areaname = "Hobbiton";
   land = "the Shire";
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   
   extraline = "The rolling plain goes on and on in all directions, "+
   "southeast a path leads toward a small hut.  East is a well.";
   
   
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
   
   add_exit(EAST_R_DIR + "wplace","east");
   add_exit(EAST_R_DIR + "er14s","northwest");
   add_exit(EAST_R_DIR + "forge","southeast");
    
}

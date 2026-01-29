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
   
   extraline = "The small hamlet of Bywater lies to the north of "+
   "the Great East Road at this point, with the village of Hobbiton "+
   "beyond Bywater.  To the east lies the Three Farthing Stone, where "+
   "the boundaries of the West, East and South Farthings meet.  "+
   "To the south, a road winds through the Green Hill Country, "+
   "part of the region known as Tookland.";
   
   add_item(({"stone","three farthing stone"}),"This stone marks the "+
      "boundaries between the divisions of the Shire, known as "+
      "Farthings.\n");
   
   add_item(({"bywater","hamlet"}),
      "The hamlet of Bywater lies beside a stream known as The Water, "+
      "running from beyond Hobbiton to the west, to the Brandywine "+
      "River.  Bywater has a well known inn, The Green Dragon, that "+
      "is well worth a visit.\n");
   
   add_item(({"hobbiton","village"}),
      "Past Bywater lies the village of Hobbiton, home of Bag End."+
      "A stream, known as The Water, runs through the middle of "+
      "Hobbiton, on its way to the Brandywine River to the East.  "+
      "Hobbiton is the pride of the Shire, with much to offer "+
      "to weary travellers.\n");
   
   add_item(({"tookland","green hill country"}),
      "The Took Hills to the south are the homeplace for the Tooks, "+
      "one of the great families of hobbits.  These hills have produced "+
      "many a leader of the Shire.\n");

   add_exit(EAST_R_DIR + "er13","west",0,2);
   add_exit(EAST_R_DIR + "er15","east",0,2);
   add_exit(EAST_R_DIR + "er14n","north",0,2);
   add_exit(EAST_R_DIR + "er14s","south",0,2);
}

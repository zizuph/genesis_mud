#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "not far from"; /* Distance from areaname */
   areaname = "Bywater";
   land = "the Shire";
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "The small hamlet of Bywater lies north, between "+
   "The Great East Road and The Water, a tributary of the "+
   "Brandywine river. West of Bywater is the village of Hobbiton, "+
   "a place well worth visiting. Because of a recent overflowing of "+
   "The Water, Bywater is currently filled with mud and other "+
   "debris. Hobbits are a very proud race and wish no visitors "+
   "to Bywater until the clean up is complete.";
   
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
   
   add_exit(EAST_R_DIR + "er14","south",0,2);
   add_exit(EAST_R_DIR + "er15n","east",0,2,1);   
}


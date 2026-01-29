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
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "The village of Hobbiton is visible north of "+
   "the Great East Road at this point, past the fields that line "+
   "the road.  To the east is a cross-road, with roads leading "+
   "to Bywater to the north, and the Green Hill Country to the "+
   "south, while the Great East Road continues on towards "+
   "Bree.  To the west lies the hamlet of Waymeet, situated "+
   "on another cross-road.";
   
   add_item(({"cross-road","cross-roads"}),"These cross-roads "+
      "mark the intersection of minor roads with the Great East Road.\n");
   
   add_item(({"field","fields"}),"Fields line the road, providing "+
      "valuable crops for the inhabitants of the Shire.\n"); 
   
   add_item("bywater",
      "The hamlet of Bywater lies beside a stream known as The Water, "+
      "running from beyond Hobbiton to the west, to the Brandywine "+
      "River.  Bywater has a well known inn, The Green Dragon, that "+
      "is well worth a visit.\n");
   
   add_item("waymeet",
      "The hamlet of Waymeet is situated on a cross-road leading "+
      "south towards the Took Hills, and north towards the North "+
      "Farthing.  Waymeet does a good trade with travellers using "+
      "the Great East Road.\n");
   
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
   
   add_exit(EAST_R_DIR + "er12","west",0,3);
   add_exit(EAST_R_DIR + "er14","east",0,3);
   add_exit(HOBTON_DIR + "er172","north",0,2);
   add_exit(EAST_R_DIR + "er13s","south",0,2,1);
}

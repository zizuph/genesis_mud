#pragma save_binary
#pragma strict_types

#include "local.h";

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "outside of"; /* Distance from areaname */
   areaname = "Greenholm";
   land = "Eriador";
   areatype = 8;
   areadesc = "flat meadow";
   grass = "green";
   
   extraline = "The hobbit village Greenholm lies just a bit east "+
                     "of here, on the other side of The Bounds, the line "+
                     "marking the western limit of the Shire.  Within "+
                     "The Bounds, hobbits have absolute authority, given "+
                     "to them by King Argeleb II of Arnor many hundreds "+
                     "of years ago.  The Great East Road leads west towards "+
                     "Mithlond and east to Greenholm and Michel Delving.";

   add_item("greenholm","The village lies on the near side of the Far Downs.\n");
   add_item(({"village","hobbit village"}),
   "Downs.\n");

   add_item(({"bounds","the bounds","limit","western limit"}),
   "The Bounds, originally drawn by King Argeleb II of Arnor extend from "+
   "The West Farthing, just to the east all the way to the Baranduin river "+
   "forty leagues away. The North Farthing and the South Farthing are north "+
   "and south of the road.  More than twenty leagues to the east lies the Three "+
   "Farthing stone which marks the intersection of the West, South and East "+
   "farthings.\n");

   add_item("mithlond","Mithlond lies seven leagues to the west.\n");
   add_item("michel delving","Michel Delving is on the other side of the "+
   "Far Downs.\n");

   add_exit(EAST_R_DIR + "er4","west");
   add_exit(EAST_R_DIR + "er6","east");
   add_exit(EAST_R_DIR + "er4s","southwest",0,2,1);
   add_exit(EAST_R_DIR + "er5s","south",0,2,1);
   add_exit(EAST_R_DIR + "er5n","north",0,2,1);

}

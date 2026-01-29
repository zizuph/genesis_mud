#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{   
   area = "not far from"; /* Distance from areaname */
   areaname = "Mithlond";
   land = "Eriador";
   areatype = 8;
   areadesc = "harbour-area";
   grass = "silvery green";
   
   extraline = "The East Road leads from Grey Havens to Rivendell. "+
   "Along its path lie the towns and cities of the Shire and "+
   "many dangers and adventures, great and small.  To the east lie "+
   "Michel Delving, Hobbiton, Bree, and Rivendell, in that order. "+
   "Just east of here stand the Tower Hills. To the north and "+
   "south fields of Eriador surround the Great East Road.";
   
   add_item(({"field","fields","fields of Eriador"}),
   "The fields are cloaked in a lush green and covered with "+
   "vegetation. The smell of herbs entices you off the road.\n");
   
   add_item(({"tower hills","tower","hills"}),
   "The Tower Hills stand just to your east, three towers upon them. "+
   "The closest to you is Elostirion which is said to house a great power!\n");
   
   add_exit(EAST_R_DIR + "er1s","south",0,2,1);
   add_exit(EAST_R_DIR + "er1n","north",0,2,1);
   add_exit(GREY_H_DIR + "shore","west");
   add_exit(EAST_R_DIR + "er2","east");

/*
   ANIMALMAKER->load_me();
   SANIMALMAKER->load_me();
*/
}

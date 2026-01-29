#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "not far"; /* Distance from areaname */
   areaname = "the West Farthing";
   land = "the Shire";
   areatype = 10;
   areadesc = "wide valley";
   grass = "deep green";
   
   extraline = "The village of Greenholm lies to the west and north, while "+
   "the vast green valley between the Far Downs and the White Downs stretches "+
   "out like a carpet.  Flat is the ground here, very arable, quite good "+
   "for agriculture.  At the reaches of your vision you can make out small fences "+
   "used by farmers to keep their livestock from roving too far.  To the east lies "+
   "Michel Delving upon the White Downs, where the Mayor of the Shire holds "+
   "residence.  Not far to the west lie the western Bounds, where the Shire ends "+
   "and Eriador begins.";

   add_item(({"village","greenholm"}),
   "The village Greenholm lies on the Far Downs, the burrows dug out of the "+
   "hillside.\n");

   add_item(({"far downs","valley","white downs","carpet","green valley"}),
   "This green valley extends as far north and south as well "+
   "as to the Far Downs in the west and the White Downs in the east. The surface "+
   "is as flat as an anvil.\n");

   add_item(({"ground","flat","arable ground"}),
   "The ground here is very fertile, black to the eye but gold to the pocket.\n");

   add_item(({"fences","farmers","livestock"}),
   "The fences are rather sloppily made of wire and wood, the farmers "+
   "obviously not worried about failing to recover a sheep or cow.\n");

   add_item(({"michel delving","mayor","mayor of the shire"}),
   "Michel Delving lies to the east on the White Downs, where the Mayor "+
   "holds the Midsummer festival.\n");

   add_item(({"bounds","western bounds","eriador"}),
   "The Bounds divide the Shire from the rest of Eriador.  The western "+
   "bounds are almost a league to the west at the moment.\n");

   add_exit(EAST_R_DIR + "er6","west");
   add_exit(EAST_R_DIR + "er8","east");
   add_exit(EAST_R_DIR + "er7n","north",0,2,1);
   add_exit(EAST_R_DIR + "er7s","south",0,2,1);
}

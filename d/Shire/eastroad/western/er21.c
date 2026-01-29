#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;


void
create_er_room()
{
   area = "just west of";
   areaname = "the Brandywine Bridge";
   land = "Eriador";
   areatype = 10;
   areadesc = "wide level plain";
   grass = "green";
   
   extraline = "The East Road here passes through a wide level plain, "+
   "obviously created by numerous floods of the Baranduin.  "+
   "To the west are many small, but important villages. "+
   "To the east is the Brandywine Bridge itself and west the "+
   "Shire extends more than forty leagues to Greenholm.";
   
   add_item(({"plain","level plain","wide plain","wide level plain","flood plain"}),
      "The flood plain is filled with small trees and plants eager for "+
      "water, the source of all life.\n");
   add_item(({"tree","trees","small trees","plant","plants","small tree"}),
      "The small trees and plants here thrive on the water they receive "+
      "from the Brandywine.\n");
   add_item(({"river","baranduin river","brandywine river"}),
      "The river, just to the east is a milky brown, and it lazes along "+
      "to the south at a slow pace.\n");
   add_item(({"bridge","baranduin bridge","brandywine bridge","bridge of stonebows"}),
      "The Bridge of Stonebows is very ancient, having been built "+
      "long ago for the travels of Elves and Men.\n");
   
   add_exit(EAST_R_DIR + "er20","west",0,2);
   add_exit(EAST_R_DIR + "er21a","east",0,2);
   add_exit("/d/Shire/eastroad/village/whit/whitroad1", "south");
}


// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({5,3}); }
 
create_khalakhor_room()
{
   extra="There is a rather large boulder sitting in the middle of the "+
         "courtyard.";
   add_item("boulder",
      "It is a rather large boulder with smooth sides set in the "+
      "middle of the grassy courtyard. An inscription is sculpted "+
      "across it.\n");
   add_item("inscription","It is sculpted on the boulder.\n");
   add_cmd_item("inscription", "read","KIRK SOLSHEYDERI.\n");
   create_court("south");
   add_exit("ksanct2",    "north");
   add_exit("street5n", "south");
   add_exit("kabbey",    "east");
   add_exit("kpriory.c",    "west");
}

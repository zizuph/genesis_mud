#include "defs.h"
inherit PROAD;
 
public int* query_local_coords() { return ({15,6}); }
 
public void create_khalakhor_room()
{
   extra="The road rises sharply from the rocky shoreline here up the "+
         "base of the hill to the west.";
   create_proad();
   add_exit("proad5","southwest");
   add_exit("proad7","east");
}

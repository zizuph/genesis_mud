#include "defs.h"
inherit PROAD;
 
public int* query_local_coords() { return ({12,6}); }
 
public void create_khalakhor_room()
{
   extra="The road rises sharply here as it leads further up the hill "+
         "to the west.";
   create_proad();
   add_exit("proad2","west");
   add_exit("proad4","southeast");
}

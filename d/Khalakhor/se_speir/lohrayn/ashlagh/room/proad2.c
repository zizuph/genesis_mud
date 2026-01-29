#include "defs.h"
inherit PROAD;
 
public int* query_local_coords() { return ({11,6}); }
 
public void create_khalakhor_room()
{
   create_proad();
   add_exit("proad1","northwest");
   add_exit("proad3","east");
}

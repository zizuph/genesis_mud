#include "defs.h"
inherit PROAD;
 
public int* query_local_coords() { return ({13,7}); }
 
public void create_khalakhor_room()
{
   create_proad();
   add_exit("proad3","northwest");
   add_exit("proad5","east");
}

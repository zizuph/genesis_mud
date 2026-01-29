/* Kirk of Port City - Upper Corridor of abbey */
#include "defs.h"
inherit  ROOM+"ucorr";
 
/* room definition */
void create_khalakhor_room() {
   init_ucorr();
   set_long(
      query_long()+"There are entrances to two chambers here, to the "+
      "north and west.\n");
   add_exit("ulib1",    "north");
   add_exit("ucorr4",   "south");
   add_exit("uclassrm", "west");
}

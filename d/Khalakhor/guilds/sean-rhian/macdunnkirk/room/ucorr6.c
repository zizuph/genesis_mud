/* Kirk of Port City - Upper Corridor of abbey */
#include "defs.h"
inherit  ROOM+"ucorr";
 
/* room definition */
void create_khalakhor_room() {
   init_ucorr();
   set_long(
      query_long()+"To the west is the entrance to one of the chambers "+
      "of the abbey.\n");
   add_exit("ucorr5",   "north");
   add_exit("ucorr7",   "south");
   add_exit("uconclave",  "west");
}

/* Kirk of Port City - Upper Corridor of abbey */
#include "defs.h"
inherit  ROOM+"ucorr";
 
/* room definition */
void create_khalakhor_room() {
   init_ucorr();
   set_long(
      query_long()+"There is an entrance to one of the abbey chambers "+
      "to the west.\n");
   add_exit("ucorr3",   "north");
   add_exit("ucorr5",   "south");
   add_exit("usacristy","west");
}

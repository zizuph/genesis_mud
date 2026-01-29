/* Kirk of Port City - Upper Corridor of abbey */
#include "defs.h"
inherit  ROOM+"ucorr";
 
/* room definition */
void create_khalakhor_room() {
   init_ucorr();
   set_long(
      query_long()+"There is a small spiral staircase here which circles "+
      "down to the lower level.\n");
   add_item(({"stairs","steps","staircase"}),
      "The staircase is made of long, thing slabs of stone, which spiral "+
      "down to the floor below in a half turn. There is no bannister, so "+
      "you should be careful should you choose to descend them.\n");
   add_exit("ucorr6",   "north");
   add_exit("kcorr7",   "down");
}

/* Kirk of Port City - Upper Corridor of abbey */
#include "defs.h"
inherit  ROOM+"ucorr";
 
/* room definition */
void create_khalakhor_room() {
   init_ucorr();
   set_long(
      query_long()+"The faint perfumed scent of incense wafts from the "+
      "chamber to the west.\n");
   add_exit("ucorr4",   "north");
   add_exit("ucorr6",   "south");
   add_exit("uchapel",  "west");
}

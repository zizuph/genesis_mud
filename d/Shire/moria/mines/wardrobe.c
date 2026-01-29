#include "defs.h"

CONSTRUCT_ROOM {
   set_short("By the princess' wardrobe.");
   set_long("You stand by the princess' wardrobe. It seems to be completely "+
      "stripped of clothes and equipment. The room extends to the "+
      "south. Behind the wardrobe there is an eastward opening.\n");
   add_item(({"wardrobe","opening"}),"You can obviously go to the east.");
   EAST("shieldch");
   SOUTH("sleeping");
}




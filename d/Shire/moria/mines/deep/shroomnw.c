#include "defs.h"

CONSTRUCT_ROOM
{
   set_short("North-west of Big Room");
   set_long(
      "You are in the north-western corner of a big room. The ceiling "+
      "vaults too high above you to see and the floor extends evenly "+
      "to the south and to the east. Along the walls there are several "+
      "small platforms or ledges, and there is an exit in the north wall.\n");
   NORTH("bottom");
   SOUTH("shroomsw");
   SOUTHEAST("shroomse");
   EAST("shroomne");
   add_item(({"ceiling","corner","floor","exit"}),
      "There really isn't much else to tell.");
   add_item(({"platforms","ledges"}),
      "I guess you would have to go there to investigate those.");
}

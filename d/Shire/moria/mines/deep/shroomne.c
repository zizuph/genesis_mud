#include "defs.h"

CONSTRUCT_ROOM
{
   set_short("North-east of Big Room");
   set_long(
      "You are standing in a corner of a big room.\n"+
      "The ceiling vaults high above you and the floor extends evenly "+
      "to the south and to the west. Along the walls there are several "+
      "small platforms or ledges, and there is an exit in the wall to "+
      "the east.\n");
   WEST("shroomnw");
   SOUTHWEST("shroomsw");
   SOUTH("shroomse");
   EAST("crawling");
   add_item(({"ceiling","corner","floor","exit"}),
      "There isn't much else to tell really.");
   add_item(({"platforms","ledges"}),
      "I guess you would have to go there to investigate those.");
}

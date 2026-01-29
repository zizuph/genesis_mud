/* rd_cw_03: Caravan Way section 3 (between shops). */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("western caravan way");
    set_long ("A thick mob pushes from the west, where Caravan Gate can "+
              "be seen, and the east where lies the great cistern of Tyr. "+
              "A great deal of business is being done to the north and "+
              "south, respectively the merchants of armour and weapons.\n");
    add_item(({"mob", "thick mob"}), "A much larger proportion of "+
              "the tougher races (half-giants, dwarves, and mul), as well "+
              "as an unusual array of foreign merchants make up the "+
              "local allotment of street life.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TZ_CARAVAN+"armrmrch.c", "north", 0, 1);
    add_exit(TZ_CARAVAN+"rd_cw_04.c", "east", 0, 1);
    add_exit(TZ_CARAVAN+"weapmrch.c", "south", 0, 1);
    add_exit(TZ_CARAVAN+"rd_cw_02.c", "west", 0, 1);
}

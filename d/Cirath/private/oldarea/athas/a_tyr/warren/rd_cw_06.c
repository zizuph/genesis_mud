/* rd_cw_06: Caravan Way section 6. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("commoner's road");
    set_long ("The north buzzes with activity, as people head for "+
              "the Iron Square which lies to the northeast. You can "+
              "almost feel the moisture from Tyr's cistern "+
              "from this distance.  In direct contrast to the richness "+
              "in that direction, the poorest sections of the city "+
              "lie in all southerly directions.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TZ_CARAVAN+"rd_cw_05.c", "north", 0, 1);
    add_exit(TZ_WARREN+"slum4.c", "southeast", 0, 1);
    add_exit(TZ_WARREN+"hut2.c", "south", 0, 1);
    add_exit(TZ_WARREN+"rd_vr_03.c", "southwest", 0, 1);
}

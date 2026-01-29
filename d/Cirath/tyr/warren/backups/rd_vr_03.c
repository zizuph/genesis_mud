/* rd_vr_03: Virl road section 3. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("central sul street");
    set_long ("Here Sul Street runs along the outer wall; Northwest to "+
              "Caravan Gate and southeast to the slums.  Several homes of "+
              "Tyr's less fortunate citizens are north and east, and to the "+
              "northeast is Commoner's Road and what appears to be the "+
              "way to the main square.\n");
    add_item("wall", "The massive stone wall keeps raiders out and the "+
             "unlucky citizens in.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"rd_vr_04.c", "northwest", 0, 1);
    add_exit(TYR_WARREN+"hut5.c", "north", 0, 1);
    add_exit(TYR_WARREN+"rd_cw_06.c", "northeast", 0, 1);
    add_exit(TYR_WARREN+"hut4.c", "east", 0, 1);
    add_exit(TYR_WARREN+"rd_vr_02.c", "southeast", 0, 1);
}

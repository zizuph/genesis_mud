/* rd_vr_04: Virl road section 4. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("north sul street");
    set_long("Gradually Sul Street begins to bend to the southeast, "+
             "where it charges full on into the poor quarter of the city. "+
             "Routine Templar sweeps keep the dwellers from moving this far "+
             "towards the central city, lest they mingle with those who "+
             "make use of Caravan Gate to the north.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TZ_CARAVAN+"rd_cw_01.c", "north", 0, 1);
    add_exit(TZ_WARREN+"rd_vr_03.c", "southeast", 0, 1);
}

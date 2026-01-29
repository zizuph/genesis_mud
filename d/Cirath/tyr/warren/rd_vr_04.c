/* rd_vr_04: Virl road section 4. */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
    ::create_room();
    set_short("north sul street");
    set_long("Gradually Sul Street begins to bend to the southeast, "+
             "where it charges full on into the poor quarter of the city. "+
             "Routine Templar sweeps keep the dwellers from moving this far "+
             "towards the central city, lest they mingle with those who "+
             "make use of Caravan Gate to the north.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_CARAVAN+"rd_cw_01.c", "north", 0, 1);
    add_exit(TYR_WARREN+"rd_vr_03.c", "southeast", 0, 1);
}

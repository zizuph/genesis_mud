/* rd_vr_01: Virl road section 1. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("east end of sul street");
    set_long ("Though no great piece of work in the best of areas, Sul Street "+
              "is literaly crumbling as it approaches the slums to the east "+
              "and northeast. The footing is considerably better to the west "+
              "or even in the poor hovel to the north.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"rd_vr_02.c", "west", 0, 1);
    add_exit(TYR_WARREN+"hut3.c", "north", 0, 1);
    add_exit(TYR_WARREN+"slum1.c", "northeast", 0, 1);
    add_exit(TYR_WARREN+"slum2.c", "east", 0, 1);
}

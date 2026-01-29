/* rd_vr_02: Virl road section 2. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("eastern sul street");
    set_long ("Now deep in the poorer sections of Tyr, Sul Street becomes "+
              "more twisted and unkempt. Entire sections are flooded by "+
              "mud, where the sewage system has been inadequate to the "+
              "task of absorbing all the waste. Several small huts are "+
              "to the north, while Sul proceeds east and northwest.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"rd_vr_03.c", "northwest", 0, 1);
    add_exit(TYR_WARREN+"hut4.c", "north", 0, 1);
    add_exit(TYR_WARREN+"rd_vr_01.c", "east", 0, 1);
}

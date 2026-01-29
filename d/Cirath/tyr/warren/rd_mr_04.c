/* rd_mr_04: Market road section 4. */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void create_room()
{
    ::create_room();
    set_short("west end of market road");
    set_long ("Market Road comes to an abrupt end just east of what appears "+
              "to be the city slums. From the northeast echo the loud "+
              "shouts of hawkers selling their merchandise, and to the south "+
              "lies the entrance to a run-down house.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"slum3.c", "west", 0, 1);
    add_exit(TYR_MARKET+"rd_mr_05.c", "northeast", 0, 1);
    add_exit(TYR_WARREN+"hut1.c", "south", 0, 1);
}

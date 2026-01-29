/* ironsqr7: South section of Iron Square. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("south of iron square");
    set_long("While somewhat crowded, this portion of the Iron Square "+
             "is of little importance. Not very near to the Ziggurat, the "+
             "cistern, any important houses, or even primary roads, it "+
             "serves only as part of the shortest route between Caravan "+
             "Way and Market Road.\n");

    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM

    add_exit(TYR_MERCHANT+"ironsqr6.c", "west", 0, 1);
    add_exit(TYR_MERCHANT+"ironsqr8.c", "east", 0, 1);
}

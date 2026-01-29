/* ironsqr2: North section of Iron Square. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("north of iron square");
    set_long("Nestled between where the High Road and Pandora's End enter "+
             "Iron Square to the west and east respectively, and claimed "+
             "by no particular merchant house, this section of the square "+
             "is relatively quiet. There is some minor traffic between "+
             "the two roads, but between that and the stark image of the "+
             "Ziggurat looming to the east, there is nothing of note.\n");

    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM

    add_exit(TZ_MERCHANT+"ironsqr1.c", "west", 0, 1);
    add_exit(TZ_MERCHANT+"ironsqr3.c", "east", 0, 1);
}

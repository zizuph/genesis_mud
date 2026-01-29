/* ironsqr5: East section of Iron Square. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("east of iron square");
    set_long("Enveloped in the dark shadow of Kalak's Ziggurat just to "+
             "the east, this section of the Iron Square of Tyr seems "+
             "devoid of soul or life. Scarce few ever need or want to "+
             "venture to this spot, instead going out of their way to "+
             "find another route. Even the buildings to the west, owned "+
             "by the mighty merchant houses of Tyr, have few windows in "+
             "this direction and none of those open. Escape to more "+
             "'pleasant' sections of the square lie south and north.\n");

    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM

    add_exit(TYR_MERCHANT+"ironsqr3.c", "north", 0, 1);
    add_exit(TYR_ZIG+"out_base.c","east",0,1);
    add_exit(TYR_MERCHANT+"ironsqr8.c", "south", 0, 1);
}

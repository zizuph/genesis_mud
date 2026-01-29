/*      This is the upstairs room of the farmhouse west of pelargir
 *
 *
 *
 *      Copyright (C) Jim Fraser 1996
 */

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h";

void
create_room()
{
    set_short("The hayloft.");
    set_long(BSN("There is very little to see in the hayloft of the "
        + "farmhouse. There are a few blankets, a pillow or two, and lots "
        + "of straw. This is obviously where the farmer and his family sleep."));

    add_exit(LEB_DIR +"rroad/rfarm", "down", 0, 2);

    add_item(({"blanket", "blankets",}),BSN("They look quite warm."));
    add_item(({"pillow", "pillows",}),BSN("The pillows are filled with "
        + "feathers of some sort. They feel very soft."));
    add_item(({"hay", "straw",}),BSN("The straw that the farmer and his family "
        + "sleep on is fresh smelling.  You realized it is probably changed often."));

}

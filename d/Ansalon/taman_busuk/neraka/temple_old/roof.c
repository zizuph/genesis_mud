/* Ashlar, 06 Jul 98 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit INNER_OUT;

void
reset_neraka_room()
{
}

void
create_neraka_room()
{
    set_short("on the roof of the temple");
    set_extra_long("This is a round platform on the roof of the temple. A railing " +
    "surrounds the platform, to protect against the risk of falling off. " +
    "A metal ladder leads down from the middle of the platform. " +
    "Looking around, you notice the extraordinary view from up here.");

    add_item("view",
        "The view from up here is quite fantastic. You see all of Neraka " +
        "spread out below you.\n");

    add_item("platform",
        "The platform is a small enclosed area on the top of the roof " +
        "of the temple. It is surrounded by a railing.\n");

    add_item("railing",
        "The railing surrounds the platform.\n");

    add_item(({"ladder", "metal ladder"}),
        "The metal ladder leads down.\n");

    reset_room();

    add_exit(NTEMPLE + "u6", "down");

    // Yes, this is the roof of the temple.
    add_prop(NERAKA_I_IS_TEMPLE_ROOF, 1);
}



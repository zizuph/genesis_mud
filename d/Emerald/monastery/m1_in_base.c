#include "defs.h"

inherit MONASTERY_BASE;

#include <stdproperties.h>

void
create_m1_room()
{
}

nomask void
create_monastery_room()
{
    set_short("Monastery storage area");

    set_em_long("The musty storage area smells of decay.  " +
        "The walls are lined with shelves, on which are stacked " +
        "various supplies.\n");

    add_item("shelves",
        "Sturdy, wooden shelves line the walls, and are stacked " +
        "high with supplies.\n");

    add_item("supplies",
        "A wide variety of tools, mostly broken and a large number " +
        "of bags of grain and potates, which seem to be rotting, " +
        "adding to the strange mix of unpleasant odors.\n");

    add_item("tools",
        "A number of tools, many of which are used for gardening, " +
        "most of which are broken, and none of which seem at all " +
        "valuable.\n");

    add_item(({ "bags", "grain", "potatoes", "bags of grain", 
        "bags of potatoes" }),
        "Judging from the number of bags full of grain and potatoes, " +
        "the monks of this monastery don't receive shipments very often.  " +
        "A few of the bags have holes in them, probably from rats; though, " +
        "the holes do seem larger than those any kind of small vermin " +
        "would make.\n");

    remove_prop(ROOM_I_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);

    create_m1_room();
}

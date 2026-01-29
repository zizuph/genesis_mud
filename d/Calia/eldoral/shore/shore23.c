#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    main += "Several large boulders have taken up residence " +
        "on the shoreline north of here, making further " +
        "progress that way impossible. ";
    add_item(({"boulders", "large boulders"}),
        "They aren't particularly intimidating, but you " +
        "feel fairly sure there's nothing of any real " +
        "interest beyond them to worry about anyway.\n");
    create_direction("east");

    add_exit(SHORE + "shore22", "southeast");
    add_exit(FOREST + "e_forest_32", "south", "@@woods_msg");
    add_exit(FOREST + "e_forest_33", "west", "@@woods_msg");
}

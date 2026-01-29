#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    main += "The ground west of here is host to " +
        "several very large boulders, further passage " +
        "that way is impossible. ";
    add_item(({"boulder", "boulders","large boulders"}),
        "The boulders are quite common, despite their " +
        "size, just large masses of some granite-like " +
        "stone that has been lying here for countless " +
        "years.\n");
    create_direction("east");

    add_exit(SHORE + "shore16", "north");
    add_exit(SHORE + "shore14", "south");
}

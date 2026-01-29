#include "defs.h"

inherit RAVBASE;

public int
go_in()
{
    write("You step inside the dark opening, and enter the fetid " +
        "air of the caverns.\n");
    return 0;
}

public void
create_room()
{
    create_ravine();
    main += "The forest here ends abruptly to the south against " +
        "the vertical wall of the ravine. A dark opening stands " +
        "before you leading into the cliffside.\n";
    add_item(({"wall","cliffside","opening"}),
        "The raving wall rises thirty or forty feet vertically " +
        "into the air, and appears impossible to climb. A dark " +
        "opening in the base invites entry, however.\n");
    set_long(main + "\n\n");
    add_exit(RAVINE + "rav2", "north");
    add_exit(CAVERNS + "cav37", "south", "@@go_in");
}

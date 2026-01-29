inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("Path");
    set_long(break_string(
	  "This is an old, almost not visible path, "
	+ "leading south from The Great Eastroad. "
	+ "Far south spooky hills rise from the moist air, "
	+ "the tops of the tallest can be seen through the "
	+ "surrounding fog.\n",70));

    add_exit(ER_DIR + "er25s", "north");
    add_exit(DOWNS_DIR + "slope2", "south");
}

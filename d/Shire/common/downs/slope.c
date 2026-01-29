inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("Slope");
    set_long(break_string(
	  "You are standing on a steep slope, "
	+ "that climbs south to a spooky hill. "
	+ "Far away south, barely in sight, "
	+ "behind a lower part of the slope, "
	+ "you can vaguely see a line of trees.\n",70));

    add_exit(DOWNS_DIR + "slope2", "north");
    add_exit(DOWNS_DIR + "stone", "south");
}

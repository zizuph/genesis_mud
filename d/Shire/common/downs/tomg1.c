inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"

create_room() {
    set_short("Outside a cottage");
    set_long("@@my_long");

    add_exit(BREE_DIR + "tome", "east");
    add_exit(DOWNS_DIR + "tomg2", "south");
    add_exit(DOWNS_DIR + "down3", "north");
}

my_long() {
    string the_long;

    the_long = "You are standing outside Tom Bombadil's cottage, on top of "
	+ "a small hill. To the west the old forest rises, and to the north "
	+ "you see hills, and more hills.";

    if (this_player()->query_skill(SS_LOC_SENSE) > 20)
	the_long += " They must be the feared Barrow Downs.\n";
    else
	the_long += "\n";

    return break_string(the_long,70);
}

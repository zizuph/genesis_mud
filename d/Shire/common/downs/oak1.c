inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"


create_room() {
    set_short("Tree");
    set_long(break_string(
	  "You are in the middle of a room of leaves. To the northeast you "
	+ "can barely make out Tom's cottage through the walls of green. "
	+ "The tree still goes up a long way above you. "
	+ "You wonder what might be up there.\n",70));

    add_item("cottage", break_string(
	  "Tom Bombadil's cottage lies far away to the northwest. You can "
	+ "only see its roof between the trees of the old forest.\n",70));

    add_exit(DOWNS_DIR + "oaktop", "up");
    add_exit(DOWNS_DIR + "tomg2", "down");
}

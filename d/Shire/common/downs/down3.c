inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"


create_room() {
    set_short("Valley");
    set_long(break_string(
	  "This is the south end of a valley that stretches in the east "
	+ "west direction, between the hills and downs. "
	+ "South you can climb a hill towards a nice, "
        + "little cottage, where you also spot a huge oak tree.\n",70));

    add_item(({"tree","oak","oak tree", "huge oak tree"}), break_string(
          "The oak tree is too far away to examine more closely. From here "
        + "you only see its huge green roof of leaves.\n",70));

    add_exit(DOWNS_DIR + "tomg1", "south");
    add_exit(DOWNS_DIR + "down4", "north");
}

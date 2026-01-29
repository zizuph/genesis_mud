#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test2", "northwest");
    add_exit(TEST_DIR + "test3", "north");
    add_exit(TEST_DIR + "test9", "south");
    add_exit(TEST_DIR + "test8", "southwest");
    add_exit(TEST_DIR + "test5", "west");
}

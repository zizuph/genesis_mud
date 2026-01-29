#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test3", "east");
    add_exit(TEST_DIR + "test6", "southeast");
    add_exit(TEST_DIR + "test5", "south");
    add_exit(TEST_DIR + "test4", "southwest");
    add_exit(TEST_DIR + "test1", "west");
}

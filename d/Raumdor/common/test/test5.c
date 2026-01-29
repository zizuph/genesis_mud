#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test1", "northwest");
    add_exit(TEST_DIR + "test2", "north");
    add_exit(TEST_DIR + "test3", "northeast");
    add_exit(TEST_DIR + "test6", "east");
    add_exit(TEST_DIR + "test9", "southeast");
    add_exit(TEST_DIR + "test8", "south");
    add_exit(TEST_DIR + "test7", "southwest");
    add_exit(TEST_DIR + "test4", "west");
}

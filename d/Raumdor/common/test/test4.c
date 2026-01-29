#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test1", "north");
    add_exit(TEST_DIR + "test2", "northeast");
    add_exit(TEST_DIR + "test5", "east");
    add_exit(TEST_DIR + "test8", "southeast");
    add_exit(TEST_DIR + "test7", "south");
}

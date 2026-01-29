#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test6", "south");
    add_exit(TEST_DIR + "test5", "southwest");
    add_exit(TEST_DIR + "test2", "west");
}

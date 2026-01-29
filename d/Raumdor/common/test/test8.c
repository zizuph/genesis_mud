#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test4", "northwest");
    add_exit(TEST_DIR + "test5", "north");
    add_exit(TEST_DIR + "test6", "northeast");
    add_exit(TEST_DIR + "test9", "east");
    add_exit(TEST_DIR + "test7", "west");
}

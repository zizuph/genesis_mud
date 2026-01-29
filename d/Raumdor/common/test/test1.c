#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test2", "east");
    add_exit(TEST_DIR + "test5", "southeast");
    add_exit(TEST_DIR + "test4", "south");
}

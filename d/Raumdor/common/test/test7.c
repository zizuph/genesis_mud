#include "defs.h"
inherit TEST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(TEST_DIR + "test4", "north");
    add_exit(TEST_DIR + "test5", "northeast");
    add_exit(TEST_DIR + "test8", "east");
}

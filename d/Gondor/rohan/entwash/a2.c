#pragma strict_types

inherit "/d/Gondor/rohan/entwash/stream.c";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_flow("east");

    add_exit(ENTWASH_DIR + "a1", "southwest");
    add_exit(ENTWASH_DIR + "a3", "east");
}

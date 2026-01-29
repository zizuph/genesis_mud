#pragma strict_types

inherit "/d/Gondor/rohan/entwash/stream.c";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_river("Anduin");
    set_flow("south");

    add_exit(ENTWASH_DIR + "a2", "west");
    add_exit(ENTWASH_DIR + "a4", "northwest");
}

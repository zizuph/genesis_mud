#pragma strict_types

inherit "/d/Gondor/rohan/entwash/entwash.c";

#include "/d/Gondor/defs.h"

void
create_swamp()
{
    add_exit(ENTWASH_DIR + "ent1d", "southwest");
    add_exit(ENTWASH_DIR + "ent1f", "east");
}

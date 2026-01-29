/* -*- Mode: C -*-
 * Sewer j-06.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "i-07", "southwest", 0, 2);
    add_exit(DOL_SEWER + "k-07", "southeast", 0, 2);
    reset_room();
}

void
reset_room()
{
    if (!present("rat"))
	clone_object("/d/Gondor/common/npc/rat")->move(this_object());
}

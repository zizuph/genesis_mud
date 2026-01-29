/* -*- Mode: C -*-
 * Sewer f-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

int
steep()
{
    write("Eh, climb up here? The tunnel to the south is too steep " +
	  "and slimy for you to climb.\n");
    return 1;
}

void
create_sewer()
{
    set_checkpoint("d-08");

    add_exit(DOL_SEWER + "e-07", "northeast", 0, 2);
    add_exit(DOL_SEWER + "void", "south", &steep(), 2);
}

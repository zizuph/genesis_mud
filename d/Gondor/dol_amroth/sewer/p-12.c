/* -*- Mode: C -*-
 * Sewer p-12.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    set_checkpoint("p-12");

    add_exit(DOL_SEWER + "o-11", "northwest", 0, 2);
    add_exit(DOL_SEWER + "q-11", "northeast", 0, 2);
    add_exit(DOL_SEWER + "o-12", "west", 0, 2);
}

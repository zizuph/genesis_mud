/*
 * /d/Gondor/mordor/ungol/stairs/hole8.c
 *
 * Olorin, 21 December 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/stairs/std_hole";

#include "/d/Gondor/defs.h"
#include "ravine.h"

void
create_hole()
{
    set_short("In a narrow crevice high in the Ephel Duath");
    set_long(BSN("This is a crevice between two great piers of rock. " +
        "Tall rocks seem to be leaning over the crevice. " +
        "The ground is covered by rubble and heaps of rock that must " +
        "have fallen down from above. "+
        "To the north a narrow ravine is visible."));

    CREVICE;
    RAVINE_HOLE;
    PIERS;
    FLOOR_HOLE;

    add_exit(STAIRS_DIR + "ravine3", "north",     0, 1);
}

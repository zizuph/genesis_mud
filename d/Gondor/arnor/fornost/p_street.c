/*
 *      /d/Gondor/arnor/fornost/plaza.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_fornost()
{
    set_short("on a street in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_roof();
    add_rubble();
    add_ruins();
    add_stones();
    add_street();

    add_item(({ "flagstone", "slabs of stone" }),
    "Most of the flat slabs of rock are cracked.\n");
    add_item("building", "A roofless shell. You could possibly enter it.\n");
    add_item(({ "green area", "area" }),
    "You only discern that the area looks overgrown.\n");

    add_exit(FORNOST_DIR + "archway", "southwest", 0, 2);
    add_exit(FORNOST_DIR + "f_garden", "east", 0, 2);
}

string
set_arnor_long()
{
    string desc;

    desc = "A flagstone paved street in the ruins of Fornost. "+
    "The street is rather free of rubble. A small building, with low "+
    "walls and no roof, is beside the street. An old forge is inside "+
    "the building. Grass is growing between the flagstones. The street "+
    "continues to the southwest. A green area is to the east. ";
    desc += query_arnor_time();

    return BSN(desc);
}

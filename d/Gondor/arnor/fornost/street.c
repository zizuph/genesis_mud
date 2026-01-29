/*
 *      /d/Gondor/arnor/fornost/street.c
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
    set_short("a broken street in the ruins of Fornost");

    add_buildings();
    add_bushes();
    add_columns();
    add_grass();
    add_ground();
    add_rubble();
    add_ruins();
    add_stones();
    add_street();

    add_item("fountain",
    "The fountain is broken, no water is coming out of it.\n");
    add_item("pavement", "The pavement has been shattered by brute force.\n");

    add_exit(FORNOST_DIR + "s_square", "north", 0, 3);
    add_exit(FORNOST_DIR + "gate", "south", 0, 3);
}

string
set_arnor_long()
{
    string desc;

    desc = "Fallen and shattered "+
    "columns line a broken street in the ruins of Fornost. Through the "+
    "pavement grass and some small bushes grow. On the west side of the "+
    "street are the remains of a small fountain. The street goes north and "+
    "south. ";
    desc += query_arnor_time();

    return BSN(desc);
}

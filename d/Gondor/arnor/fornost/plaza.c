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
    set_short("a desolated plaza in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_rubble();
    add_ruins();
    add_street();
    add_item("column", "It is at least 20 feet high.\n");
    add_item("monument", "It is now in ruins.\n");
    add_item("plaza", "It is filled with rubble.\n");

    add_exit(FORNOST_DIR + "s_square", "west", 0, 3);
    add_exit(FORNOST_DIR + "l_tower", "south", 0, 3);
    add_exit(FORNOST_DIR + "outer_wall","east", 0, 3);
}

string
set_arnor_long()
{
    string desc;

    desc = "A desolated plaza in the ruins of Fornost. "+
    "In the middle of plaza was a monument. All that is left of the "+
    "monument is a single column, still "+
    "standing as if by pure chance, proudly defying the destruction of the "+
    "city. Exits are to the west, south and east. ";
    desc += query_arnor_time();

    return BSN(desc);
}

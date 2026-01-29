/*
 *      /d/Gondor/arnor/fornost/archway.c
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
    set_short("a street in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_ivy();
    add_rubble();
    add_ruins();
    add_stones();

    add_item("archway", 
    "On the archway was once something written, but it is now unreadable.\n");
    add_item("shells",
    "The low walls are the only thing remaining of the houses.\n");
    add_item("windows", "\n");
    add_item("bush", "It grows green and tall.\n");

    add_exit(FORNOST_DIR + "p_street", "northeast", 0, 3);
    add_exit(FORNOST_DIR + "s_square", "southeast", 0, 3);
}

string
set_arnor_long()
{
    string desc;

    desc = "At this part of Fornost the destruction is somewhat less. "+
    "A few roofless shells are still standing. Empty windows look out over "+
    "the street. A free standing archway frames a bush growing behind it. "+
    "Ivy grows on the archway. The road continues northeast and southeast. ";
    desc += query_arnor_time();

    return BSN(desc);
}

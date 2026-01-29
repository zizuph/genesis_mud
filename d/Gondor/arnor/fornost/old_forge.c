/*
 *      /d/Gondor/arnor/fornost/old_forge.c
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
    set_short("in the shell of a small building in Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_rubble();
    add_ruins();
    add_stones();
    add_street();

    add_item("flagstone", "\n");
    add_item("building", "\n");

    add_exit(FORNOST_DIR + "p_street", "out", 0, 2);

    reset_room();
}

string
set_arnor_long()
{
    string desc;

    desc = "In the shell of a small building in Fornost. "+
    "... a small forge ... ";
    desc += query_arnor_time();

    return BSN(desc);
}

public void
reset_room()
{
    if (!objectp(present("_cast_iron", TO)))
        clone_object("/d/Shire/common/obj/cast_iron")->move(TO);
}

/*
 *	/d/Gondor/anorien/road/rroad3.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define DID_VISIT_PELENNOR "_ranger_visited_pelennor"

public void
create_area_room()
{
    set_areadesc("grassy field");
    set_areatype(8);
    set_area("southeastern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("The walls of Pelennor arc away from you to the northwest, "+
    "surrounding the fields around Minas Tirith. To the east and south is "+
    "the great river Anduin. The road follows its curve from northeast to "+
    "the southeast.");
    add_exit(ANO_DIR + "road/rroad4", "northeast", 0, 2);
    add_exit(ANO_DIR + "road/rroad2", "southwest", 0, 2);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (IS_RANGER(ob))
        ob->add_prop(DID_VISIT_PELENNOR, 1);
}


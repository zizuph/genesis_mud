/*
 * Citadel in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CITADEL;


void
create_citadel()
{
    INDOORS;
    NO_STEEDS;
    set_short("A deserted guard room");
    set_extraline("This was once a guard room ages ago. Now it has been " +
        "desecrated and served as a torture chamber. Set in the center " +
        "of the room is an altar.");

    reset_faerun_room();
    set_add_altar();

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN,"do_search_altar");

    add_exit(CIT_DIR + "cit_3c", "north");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    ::reset_faerun_room();
    item_found = 0;
    count = 0;
}



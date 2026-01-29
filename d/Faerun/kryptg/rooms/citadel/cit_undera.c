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
    set_short("A passage beneath the Citadel");
    set_extraline("This dark passageway extends deep beneath the Citadel. " +
        "It smells musty and dank, and looks like it was abandoned ages " +
        "ago. The stone walls are cold and wet. Empty torch stands line " +
        "the walls.");

    reset_faerun_room();
    set_add_under_cit();

    add_exit(CIT_DIR + "cit_underb", "north");
    add_exit(CIT_DIR + "cit_under0", "south");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}

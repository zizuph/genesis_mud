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
    set_short("An empty room beneath the Citadel");
    set_extraline("The room is dusty and empty. It appears to have once " +
        "been used for storage but has been stripped of anything of " +
        "value. Some random debris lays scattered in the corners of the room.");

    reset_faerun_room();
    set_add_under_cit();

    add_exit(CIT_DIR + "cit_underb", "east");

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

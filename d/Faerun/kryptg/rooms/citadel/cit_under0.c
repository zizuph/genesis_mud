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
    set_short("Beneath the Citadel");
    set_extraline("This is the basement of the citadel. It is lined with s" +
        "tone blocks. They look old, yet appear in good condition. A beam " +
        "of light shines from above, illuminating the area. Empty torch " +
        "stands line both walls and a passage leads north into the darkness. ");

    reset_faerun_room();
    set_add_under_cit();

    add_exit(CIT_DIR + "cit_undera", "north");
    add_exit(CIT_DIR + "cit_1x", "up");
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

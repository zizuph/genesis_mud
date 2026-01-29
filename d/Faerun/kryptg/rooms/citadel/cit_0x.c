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
    set_extraline("This is the basement of the citadel. It is lined with " +
        "stone blocks which support the tower above. The stones look old " +
        "yet in good condition. A beam of light shines from above, " +
        "illuminating the area. Empty torch stands line both walls, " +
        "and a passage leads north into the darkness. ");

    reset_faerun_room();
    set_add_citadel_out();

    add_item(({"stands", "empty torch stands", "torch stands"}),
        "They are made of several rings attached to the walls. Each " +
        "torch stand use to hold a torch but are now dusty and empty.\n");
    
    add_exit(CIT_DIR + "cit_0a", "north");
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

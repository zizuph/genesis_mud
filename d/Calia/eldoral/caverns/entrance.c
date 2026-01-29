#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(1);
    dir_down = ({"east"});
    main += "You notice a narrow, spiral stairway winding " +
        "upwards from here. ";
    create_base();
    add_exit(CAVERNS + "cav1", "east");
    add_exit(RUIN + "catacomb_7", "up");
}

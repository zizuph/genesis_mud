#include "/d/Krynn/common/defs.h"

/* Inherit the Krynn room */
inherit OR_FILE
inherit CONQUER_BASE

#define CREATE "create_icewall_room"
#define RESET  "reset_icewall_room"

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
    reset_conquer_room();
}

/* Needed to initialize commands for war-area */
void
init()
{
    init_conquer();
    ::init();
}





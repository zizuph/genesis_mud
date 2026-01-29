#include "/d/Krynn/common/defs.h"
#include "../local.h"

/* Inherit the Krynn room */
inherit OR_FILE

/* Moved to local.h by DWM Oct 25 1999
 *
 *      #define CREATE "create_pax_room"
 *      #define RESET  "reset_pax_room"
 */

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
 *
 * By Boron Oct 25 1999:
 * Removed the nomask decleration to allow for special
 * handling in ../road/road_base.c
 */
public void
reset_krynn_room()
{
    call_other(TO, RESET);
}







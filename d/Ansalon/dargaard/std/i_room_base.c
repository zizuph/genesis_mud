#include "/d/Ansalon/common/defs.h"
#include <macros.h>

/*
 * i_room_base.c
 *
 * This is a standard local room base file for in-door rooms.
 * You should change all those XXX to something more appropiate.
 * If you are doing an area like Pax Tharkas then a proper 
 * replacement for XXX would be 'pax'.
 */

/* Inherit the Ansalon room */
inherit AR_FILE

/*
 * Change these two XXX to the proper name
 */
#define CREATE "create_dargaard_room"
#define RESET  "reset_dargaard_room"

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
}

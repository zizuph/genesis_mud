/*
 *
 *    The inside base file for the Port city of Jennison.
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/nordmaar/jennison/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* 
 *    Inherit the Ansalon room
 */
inherit AR_FILE

#define CREATE "create_jennison_room"
#define RESET  "reset_jennison_room"

/*
 *    IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 *    This function is called from the main Krynn room. It 
 *    checks whether or not the room should be reset. This 
 *    function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 *    This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 *    This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

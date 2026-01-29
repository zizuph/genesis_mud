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
    set_tell_time(random(650));
    add_tell("A cool wind suddenly blows through the room.\n");
    add_tell("A faint scream can be heard from far away.\n"); 
    add_tell("A scream of pain and agony can be heard echoing through "+
             "the room.\n");
    add_tell("You feel as if you are being watched.\n");
    add_tell("A pair of glowing red eyes looks at you from the shadows.\n");
    add_tell("You pause momentarily as the room is covered in shadows.\n");
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

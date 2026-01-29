/*
 * i_room_base.c
 */

#include "/d/Krynn/common/defs.h"

/* Inherit the Krynn room */
inherit R_FILE

/*
 * Change these two XXX to the proper name
 */
#define CREATE "create_poolbottom_room"
#define RESET "reset_poolbottom_room"

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

    add_prop(ROOM_M_NO_ATTACK, "Magical runes of tranquility have been incorporated " +
       "into the walls of the school of High Magic. There will be no violence inside " +
       "the walls of the school.\n");

    add_prop(ROOM_M_NO_STEAL, "Magical runes of tranquility have been incorporated " +
       "into the walls of the school of High Magic. There will be no thievery " +
       "against fellow students within the walls of the school.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

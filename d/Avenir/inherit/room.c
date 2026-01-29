// file name:        /d/Avenir/inherit/room.c
// creator(s):       Denis, Jul'96
// purpose:          Standard room for Avenir.
//                   Also, Smis-aware room in Avenir.
//		     
/*
 * Revisions:
 *     Lucius, Jul 2017: Miscellaneous cleanups.
 *     Lilith, Dec 2021: Added ROOM_I_INSIDE as default for all rooms.
 *     Lilith, Mar 2022: Added terrain underground to rooms. 
 */
#pragma strict_types

#include <stdproperties.h>
#include <terrain.h>
#include "/d/Avenir/smis/smis.h"

inherit SMIS_ROOM;

/*
 * Function name: create_domain_room
 * Description:   This function should be used for Avenir rooms creation code.
 */
public void
create_domain_room(void)
{
}

/*
 * Function name: create_smis_room
 * Description:   Redirects to create_domain_room
 */
public nomask void
create_smis_room(void)
{
	// Since Avenir is an entirely subterranean domain
	// Lets make sure all rooms are inside rooms
	// with underground terrain type.
	add_prop(ROOM_I_INSIDE, 1);
	set_terrain(TERRAIN_UNDERGROUND);
	
    // Since rooms default to being outside,
    // we by default allow steeds to enter rooms.
    // We can override this with the IN_IN macro later.
    add_prop(ROOM_I_ALLOW_STEED, 1);
	
    // Too many cheating teleporters doing things withing asking.
    // Block them all now, unconditionally. (Lucius)
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    create_domain_room();
}

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for Avenir rooms reset code.
 */
public void
reset_domain_room(void)
{
    // Putting this here, since it is not working when called in rooms.
    set_searched(0);
}

/*
 * Function name: reset_smis_room
 * Description:   Redirects rest to reset_domain_room
 */
public nomask void
reset_smis_room(void)
{
    reset_domain_room();
}

/*
 * Function name: query_reset_needed
 * Description:   Determines if the reset is needed through the inherit chain.
 * Returns:       1 - If reset is needed.
 */
public int
query_reset_needed(void)
{
    return (function_exists("reset_domain_room", this_object()) !=
	"/d/Avenir/inherit/room");
}

/* File         : /d/Khalakhor/guilds/tuatha/room/hut_base.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 16, 1999
 * Purpose      : This is the base room for the hut rooms in the Tuatha
 *                guild area.
 * Related Files: /d/Khalakhor/guilds/tuatha/room/tuatha_room.c
 * Comments     :
 * Modifications:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/guilds/tuatha/room/tuatha_room";

#include <stdproperties.h>

#include "../guild.h"
#include "/d/Khalakhor/sys/terrains.h"

/*
 * Function    : create_tuatha_hut
 * Description : Initializes and creates the hut room.
 * Arguments   : n/a
 * Returns     : n/a
 */
public void
create_tuatha_hut()
{
}

/*
 * Function    : create_tuatha_room (MASK)
 * Description : A masked version of the Khalakhor room creation function.
 * Arguments   : n/a
 * Returns     : n/a
 */
nomask public void
create_tuatha_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_HOUSE);
}

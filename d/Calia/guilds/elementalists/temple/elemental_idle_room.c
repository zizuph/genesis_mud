/*
 * Elemental Idle Room
 *
 * This is where elementals come to rest when they are dismissed (as opposed
 * to dispelled.
 *
 * Created by Petros, February 2013
 */

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

public void
create_temple_room()
{
    set_short("Idle room, you shouldn't see this");
    set_long("Room to keep elementals that are sent away.\n");

    add_prop("_room_i_allow_steed", 1);
    add_prop("_room_i_allow_horse", 1);
}

/*
 * jail_waiting.c
 *
 * This is a sort of waiting room for players who have
 * been knocked out by village guards and are being
 * dragged to jail. They're transed here until they
 * are needed to be in the same room as the guard draggin
 * them (in the case of the guard meeting other players,
 * for instance).
 * 
 * Khail - June 20/97
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("storage room");
    set_long("   storage room");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_M_NO_STEAL, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
}

public int
query_prevent_snoop()
{
    return 1;
}

public int
query_prevent_shadow()
{
    return 1;
}

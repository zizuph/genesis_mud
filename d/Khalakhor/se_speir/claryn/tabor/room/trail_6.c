/*
 * trail_1.c
 *
 * This is part of the trail north of Tabor Sogh.
 *
 * Khail - Jan 9/98
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include "room.h"

inherit TRAILBASE;

public void
create_khalakhor_room()
{
    create_trail();

    add_exit(ROOM + "trail_5", "northeast");
    add_exit(ROOM + "trail_7", "south");
}

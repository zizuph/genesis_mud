/* /d/Earthsea/std/room.c
 */

inherit "/std/room";

#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/sys/time.h"

void
create_earthsea_room()
{
}

nomask void
create_room()
{
    ::create_room();
    create_earthsea_room();
}

/*
 * Function name: hourly_event
 * Description:   Called hourly in rooms with interactive players
 *                present.
 */
void
hourly_event()
{
    int terrain = query_prop(ROOM_I_TERRAIN_TYPE);
    if ((terrain & TERRAIN_SALTBEACH) != TERRAIN_SALTBEACH)
    {
        return;
    }

    switch (EARTHSEA_HOUR)
    {    
        case 0:
            tell_room(this_object(), "The tide rolls in.\n");
            break;
        case 12:
            tell_room(this_object(), "The tide rolls out.\n");
            break;
    }
} 

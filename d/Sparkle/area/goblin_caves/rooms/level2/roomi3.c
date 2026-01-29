/*
 * Guard room base room
 * Boreaulam, August 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_GUARD_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    add_exit("roomh4", "north");

} /* create_room */


/*
 * Standard ship deck to be used in Krynn/Ansalon.
 *
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/ship/deck";
#include "/d/Krynn/std/room/time.c"

/*
 * Function name: init
 * Description:   Give the room commands to a player.
 */
void
init()
{
    ::init();
    add_action(check_time, "time");
}

/*
 * Standard ship deck to be used in Krynn/Ansalon.
 *
 * Ported to the new ship system - Tapakah, 08/2009
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIPROOM;
#define ROOM_I_NO_TIME "_room_i_no_time"

#include "/d/Krynn/std/room/time.c";

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

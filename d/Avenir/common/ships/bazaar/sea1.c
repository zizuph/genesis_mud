/*
 * Filename: /d/Avenir/common/ships/bazaar/sea1.c
 * Original creator: Kazz on Apr 1995
 * Purpose: water room for boat between outpost & park
 * Last update(s):
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 * Note: add_items are not needed since they can't be examined from the deck
 * Known bug(s):
 * To-do:
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Jul 2000 */

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Avenir/common/ships/bazaar/ship.h"

/*
 * Function name: create_room
 * Description  : The creator for this room
 */
public void
create_room()
{
    set_short("near the beach by a tunnel");
    set_long("The boat is near a sandy beach by a tunnel into the rock. " +
	     "The islands of the great sea are to the north.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 1);
}

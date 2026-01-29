/*
 * Filename: /d/Avenir/common/ships/bazaar/sea5.c
 * Original creator: Boriska on Sep 1995
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
    set_short("on the sea, close to shore");
    set_long("Very close is an island covered with grass and trees, " +
             "elsewhere is just the sea and great cavern.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 1);
}  

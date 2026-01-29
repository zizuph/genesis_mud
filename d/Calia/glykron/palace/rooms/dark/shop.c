/*      This is the dark palace shop.

    coder(s):   Glykron

    history:     4/8/95     typo corrected                  Maniac
                22. 8.92    /lib/shop.c inherited           Glykron

    purpose:    shop
    exits:      nw to storeroom, w to entrance and n to silent room

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    config_default_trade();
    set_short("The dark palace shop");
    set_long(BS(
	"This is a large trapezoidal-shaped room with north and west walls " +
	"sloping away from you to the southeast.  " +
	"The lighting is this room is not the best.  " +
	"There is a shopkeeper here who will allow you to buy and sell items " +
	"from him as long as he makes a profit.  " +
	"You can also use value or list commands, 'list armours', " +
	"'list weapons', 'list <name>' and 'list' works too.  " +
	"There is also a small sign to read with more instructions.  " +
	"\n"));

    add_exit(ROOM("dark_entrance"), "west", 0);
    add_exit(ROOM("dark_silent"), "north", 0);
    add_exit(ROOM("store"), "northwest", "@@wiz_check");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(ROOM("store"));
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int
wiz_check()
{
    if (this_player()->query_wiz_level())
      	return 0;
    write("Some magic force keeps you from going northwest.\n");
    say(QCTNAME(this_player()) + " tries to go northwest but fails.\n");
    return 1;
}
/*      
        This is the palace shop.
        Kroug raid handler code is installed in this room

    coder(s):   Glykron & Maniac

    history:
                6/4/96    tidied up kroug handling         Maniac
               12/12/95   vandalism possibility added       Maniac
                22/9/96   Kroug raid handler code installed Maniac 
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

inherit "/lib/shop";
inherit "/d/Calia/std/kroug_palace_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "/d/Calia/std/vandalism.c"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    config_default_trade();
    set_short("The palace shop");
    set_long(
        "This is a large trapezoidal-shaped room with north and west walls " +
        "sloping away from you to the southeast.  The shopkeeper will allow " +
        "you to buy and sell items from him as long as he makes a profit.  " +
        "You can also use value or list commands, \"list armours\", " +
        "\"list weapons\", \"list <name>\" and \"list\" work too.  " +
        "There is also a sign to read with more instructions.  " +
        "\n");

    add_item("sign", 
         "A sign with some important information on it. It seems " +
         "to be in perfect condition.\n");
    add_item_possible_vandalism("sign", "A sign with some important " +
           "information on it.", ({"dent"}), 35);

    add_exit(ROOM("light_entrance"), "west", 0);
    add_exit(ROOM("light_hardware_shop"), "north", 0);

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
    init_vandalism();
    init_shop();
}

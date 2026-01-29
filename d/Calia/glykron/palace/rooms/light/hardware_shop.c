/*  This is a hardware shop in Calia

    coder(s):  Maniac 

    history:  
               13/6/96     rest store                       Maniac
                6/4/96     tidied up kroug handling         Maniac
               22/9/95    Kroug raid code installed            Maniac
               2/2/94                     Created             Maniac 

    purpose:    shop
    exits:      w to general shop, nw to store

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

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    config_default_trade();
    set_short("The palace hardware shop");
    set_long(
        "This is a small trapezoidal-shaped room whose north and south walls " +
        "slope away from you to the east.  " +
        "This room is the hardware shop of the Calian Warriors Guild, but " +
	"everyone is welcome to use it.  " +
	"You can buy any items here, but if you want to do some selling, you " +
	"may only sell back items previously purchased at this store.  " +
	"General items can be sold next door.  " +
	"You can use value or list commands here.  " +
        "There is also a small sign to read with more instructions.  " +
        "\n");

    set_store_room(ROOM("light_hardware_store"));
    add_exit(ROOM("light_lightroom"), "west", 0);
    add_exit(ROOM("light_sleepless"), "north", 0);
    add_exit(ROOM("light_shop"), "south", 0);
    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
    query_store_room()->load_me(); 
}

int shop_hook_allow_sell(object ob)
{
    if (ob->id("_calia_hardware_shop_")) return 1;
    return 0;
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
    object tp;

    tp = TP;
    if (tp->query_wiz_level())
      	return 0;
    write("Some magic force keeps you from going northwest.\n");
    say(QCTNAME(tp) + " tries to go northwest but fails.\n");
    return 1;
}

int
do_read(string str)
{
    object tp;
    tp = TP;

    if (str == "sign")
    {
        tp->catch_msg("Commands work as for the shop next door, except " +
            "you will not be able to sell items that were not " +
            "purchased at this store.    The reason for this is " +
            "that the general store next door should be used " +
            "for this purpose.    Enjoy the shop!\n");
        return 1;
    }
    else
    {
        NF("Read what?    The sign?\n");
        return 0;
    }
}

/*
int 
do_sell(string str)
{
    TP->catch_msg("We don't buy anything here, try next door!\n");
    return 1;
}
*/

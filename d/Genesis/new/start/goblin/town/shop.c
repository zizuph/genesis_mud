/*
 * File         : /d/Genesis/new/start/goblin/town/shop.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : October 4, 1999
 * Modifications: 
 * Purpose      : The Kalerus Shop
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room";
inherit "/lib/shop";

#include <macros.h>
#include <stdproperties.h>

#define STORE  "/d/Genesis/new/start/goblin/town/stock_room"

/*
 * Prototype.
 */
int check_wizard();

void
create_room()
{
    set_short("You are in the Kalerus Shop");

    set_long("You are in the Kalerus Shop.\n" +
        "Here you may buy useful weapons, armours or gear, lamps and oil, " +
        "or whatever else is in stock. A goblin clerk stands behind the " +
        "counter. There is a sign here. A solid looking door protects the " +
        "stock room to the north. To the west, you can exit onto the " +
        "Central Plaza.\n");

    add_item(({"door", "wooden door", "solid looking door", 
        "sturdy looking door", "stock room door"}),
        "This is a simple but very sturdy looking door protecting the room " +
        "where the shopkeeper stores his wares.\n");

    add_item("counter", "It is a wooden counter.\n");

    add_cmd_item( ({ "cabinet", "door", "doors" }),
        ({ "open", "enter", "unlock" }),
        "The doors of the cabinet are closed and firmly locked. It is clear " +
        "that the door may only be opened with the clerk's permission.\n");

    add_cmd_item("sign", "read", "");

    /*
     * The shop-related initializations.
     */
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);

    /*
     * Add an exit leading to the stock room, the first parameter is the path
     * to the store, the second command to enter it and the third parameter
     * is a VBFC call to block all mortals players from using the exit.
     * We could even hide the exit from the view of players, but that is
     * beyond the scope of this example.
     */
    add_exit(STORE, "north", check_wizard);

    add_exit("cavern_c3", "west");

    set_noshow_obvious(1);
}

void
init()
{
    ::init();

    /*
     * Do this to add the shop-commands to the player.
     */
    init_shop();
}

/*
 * We do not want mortal players to walk into the cabinet and help
 * themselves. However, wizards might need to go in there if something
 * is wrong. Therefore we block their exit.
 */
int
check_wizard()
{
    /* wizards may use the exit. */
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    /* however, mortal players cannot... */
    write("The stock room is locked. You cannot get into it.\n");
    say(QCTNAME(this_player()) + " fails to enter the stock room.\n");
    return 1;
}

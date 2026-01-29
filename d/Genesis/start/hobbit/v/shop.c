/*
 *  The Hobbiton drugstore, adapted to use the new /d/Genesis/lib/shop.c
 *                               Tricky, august '93
 * Modification Log:
 * Finwe, March 2019: Hid store room exit and changed name from Drogstore 
 *                    to Shop
 */

#pragma save_binary

inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include "defs.h"
#include <stdproperties.h>

#define STORE_ROOM STAND_DIR + "shop_store"  /* Where the items are stored  */

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
    set_short("Shop of Hobbiton");
    set_long("You are inside a room that is filled with many items. In this "
     + "shop, you can buy or sell all kinds of things, such as "
     + "armours, weapons, torches, maps and other stuff alike. "
     + "If you want to know what items are for sale, you can list them. "
     + "If you want the shopkeeper's opinion on something, ask "
     + "him to value it. If you want to get rid of an item, simply sell "
     + "it. If you like something, feel free to buy it. There also is a "
     + "small sign here.\n");

    add_item(({"sign", "small sign"}), "The sign isn't that great. "
     + "something has been scribbled on it.\n");

    add_item(({"item", "items"}), 
	"There are far too much items lying around to pick one out of. You "
      + "should better take a look at the pricelist, to get an idea of what "
      + "usefull stuff you can buy here.\n");

    add_item(({"owner", "store owner"}), 
	"The owner of the store is watching you closely, so you do not get "
      + "the chance to steal anything. Besides that, he leaves you on your "
      + "own to check out the stuff that is lying around.\n");

    add_exit(STAND_DIR + "h_lane2", "east", 0);
    add_exit(STORE_ROOM, "west", "@@wiz_check",0,1);

    config_default_trade();	/* Set up the trading system */
    set_money_give_max(1000);
    		/* Copper Silver Gold Platinum  */
    set_money_give_out(({10000, 700, 40, 1}));	/* Max_pay   */
    set_money_give_reduce(({0, 7, 4, 4}));	/* Threshold */
    set_money_greed_sell("@@discriminate");
    set_store_room(STORE_ROOM);

    add_prop(ROOM_I_INSIDE, 1);	/* This is a real room */
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();	/* You MUST do this in a room-init */
    init_shop();
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    string race;

    race = this_player()->query_race();

    /* This is a Hobbit shop; they are suspicious of big folk and gnomes */
    if (race == "gnome" || race == "human" || race == "goblin")
	return 150;
    if (race == "hobbit" || race == "dwarf")
	return 100;
    return 125;
}
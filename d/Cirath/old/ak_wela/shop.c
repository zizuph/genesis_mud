/*
 * The General Supply Store in Ak Wela.
 */

inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include "/d/Cirath/common/defs.h"
#include "/sys/stdproperties.h"

#define STORE_ROOM AK_WELA_DIR + "shop_store"  /* Where the items are stored  */


void
create_room()
{
    set_short("Supply store");
    set_long("This supply store is filled with many items. Here explorers " +
             "from all over Genesis buy and sell all kinds of things, " +
             "such as armours, weapons, torches, maps and other supplies " +
             "needed to survive this harsh land.  If you want to know " +
             "what items are for sale, you can list them.  If you want " +
             "the shopkeeper's opinion on something, ask him to value " +
             "it.  If you want to get rid of an item, simply sell it.  " +
             "If you like something, feel free to buy it.\n");

    add_item(({"item", "items"}), "There are far too many items lying " +
             "around to list all of them.  The shopkeeper will, for an " +
             "honorable customer such as yourself, list the best of what " +
             "is in the store.\n");

    add_item(({"owner", "store owner"}), "The the burly man who appears " +
             "to own this store has made himself busy cleaning the back " +
             "counter.  Nonetheless, you feel his eyes constantly on " +
             "you, and realize it may have something to do with the " +
             "mirror behind the counter.  It probably would be a good " +
             "idea to be on your best behavior.\n");

    add_exit(AK_WELA_DIR + "pou_shun7", "south", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    config_default_trade();	/* Set up the trading system */
    set_money_give_max(1000);
    		/* Copper Silver Gold Platinum  */
    set_money_give_out(({10000, 700, 40, 1}));	/* Max_pay   */
    set_money_give_reduce(({0, 7, 4, 4}));	/* Threshold */
    set_store_room(STORE_ROOM);

    add_prop(ROOM_I_INSIDE, 1);	/* This is a real room */
}


void
init()
{
    ::init();	/* You MUST do this in a room-init */
    init_shop();
}


int
wiz_check()
{
    if (TP->query_wiz_rank >= WIZ_APPRENTICE)
        return 1;
    return 0;
}

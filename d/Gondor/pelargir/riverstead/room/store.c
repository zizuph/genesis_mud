/*
 *  The Settlement General Store
 *
 */
inherit "/d/Gondor/common/lib/shop";

#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

#define STORE_ROOM NCAMP_ROOM + "store_room.c"  /* Where the items are stored */

public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Settlement General Store");
    set_long("While the building looks much like the other huts in the "
        + "settlement, it is obviously a place of commerce. A counter "
        + "stands on one end of the room, and beyond it are a number of "
        + "shelves housing merchandise of all kinds. There is a poster "
        + "on the counter explaining how to trade with the shopkeeper.\n");
    set_shop_name("The Settlement General Store");
    set_keeper_file(NCAMP_NPC + "ncamp_human_male.c");
    
    add_item(({"building", "room", "hut", "place"}), &query_long());
    add_item(({"counter"}), "A large wooden counter stands between you "
        + "and the shelves of merchandise.\n");
    add_item(({"shelf", "shelves"}), "The shelves bear various items "
        + "for sale in the store.\n");
    add_item(({"merchandise"}), "Why don't you try to 'list' them?\n");

    add_exit(NCAMP_ROOM + "camp6", "out", 0);

    reset_room();
}

string
exa_poster()
{
    return "\nWelcome to the Settlement General Store!\n" +
         "You can try these instructions: \n" +
        "    buy <item> for gold and get copper back\n" +
        "    buy <item> for gold coins\n" +
        "    sell <item> for copper coins\n" +
        "    sell all  - will let you sell all items.\n" +
        "    sell <item>, sell second <item>, sell <item> 2, sell two <items>\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too.\n" +
        "    If you want a list of all the lamps available in the store,\n"+
        "    the correct syntax is: 'list lamps'.\n\n";
}

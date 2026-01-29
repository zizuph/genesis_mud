
/*   THIS SHOP IS STOLEN FROM /DOC/EXAMPLES/TRADE/SHOP.C
 *   I JUST HAD TO HAVE SOMETHING WORKING UNTILL I DESIGN MY OWN.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

/* Where the items are stored */
#define STORE_ROOM "/d/Genesis/start/human/town/store" 

void
create_room()
{
    set_short("The shop");
    set_long("\n"+
             "You're in the little village shop.\n"+
             "A scent of herbs mixed with leather, hides and tarred woodwork\n"+
             "gives the shop a cosy atmosphere. You may feel free to browse\n"+
             "but be careful not to break anything. A sign over the counter says:\n"+
             "\n"+
             "             +-----------------------------+\n"+
             "             |                             |\n"+
             "             |  Gnomes should keep their   |\n"+
             "             |  fingers off the inventory. |\n"+
             "             |                             |\n"+
             "             |  Ring the bell for service. |\n"+
             "             |                             |\n"+
             "             +-----------------------------+\n"+
             "\n"+
             "You can buy, sell, and list in here.\n"+
             "There is a brass bell on the counter.\n"+
             "");

    add_item(({"bell" }),"A little brass bell. You're probably supposed to ring it.\n"+
    "");
    add_item(({"counter" }),"An old pine-tree counter.\n"+
    "");
    add_item(({"sign" }),"");

    add_exit("/d/Sparkle/area/city/rooms/streets/market_square", "north");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");    
    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_store_room(STORE_ROOM);

    add_object(OBJ_DIR + "trash_can");
}

string
wizinfo()
{
    return ("The shop is as you can see not ready yet.\n"+
            "As soon as I have the functions I need and the time to do it\n"+
            "I will get this place in order. Also, the bell doesn't work."+
            " :)\n"+
            "Btw, I do not *dislike* gnomes but you can't blame a poor\n"+
            "shopkeeper for being careful. They are awfully greedy...\n");
}

int
ring(string str)
{
    NF("Ring what? The bell?\n");
    if (str == "bell" || str == "brass bell") {
	write("You ring the little bell.\n");
	say(QCNAME(this_player())+ " rings the bell at the counter.\n");
	return 1;
    }
    return 0;
}

void
init()
{
    ::init();

    init_shop();

    add_action(ring,"ring");
}

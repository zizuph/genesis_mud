/*
 *  Jerret's Equipment Store  *  rewritten by Arren  september 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Arren, from Olorin's shop in Minas Morgul
 *   
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/gondor/shop";

#include "/d/Gondor/common/guild/lib/shop_items.h"
#include "/d/Gondor/defs.h"

#define STORE_ROOM  RANGER_NORTH_DIR + "store_room"

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("Jerret's Equipment Store");
    set_long(BSN("This is Jerret's Equipment Store. Inside this high round "+
        "room you can sell or buy all kind of things. "+
        "The owner has made a poster, which you can read if you like. "+
        "The shopkeeper can value things if you want him to. Buying and "+
        "selling things is encouraged by the shopkeeper."));
    add_item(({"item","items"}), BS(
        "There are far too much items lying around to pick one out of. You "+
        "should better take a look at the pricelist, to get an idea of what "+
        "usefull stuff you can buy here.\n"));
    set_shop_name("Jerret's General Store");
    set_keeper_file(RANGER_NORTH_DIR+"npc/jerret");
    set_hated_race(({"goblin"}));
    set_favoured_race(({"human","elf"}));
    set_money_greed_buy("@@discriminate");
    set_money_greed_sell("@@discriminate");
    set_money_greed_change("@@discriminate");
    set_no_sell_prop(({GONDOR_M_RANGERS_NO_SELL,GONDOR_M_TIRITH_NO_SELL,GONDOR_M_ROHIRRIM_NO_SELL}));
    set_standard_equip(NORTH_EQUIP);
    add_exit(RANGER_NORTH_DIR+"w_corridor", "north", 0);
    add_exit(RANGER_NORTH_DIR+"s_corridor", "east", 0);
}

string
exa_poster()
{
  return "This is Jerret's Equipment Store\n" +
        "You can try these instructions: \n" +
        "    buy sword for gold and get copper back\n" +
        "    buy sword for gold coins\n" +
        "    sell sword for copper coins\n" +
        "    sell all  - will let you sell all items except for\n" +
        "                items you wield or wear.\n" +
        "    sell all! - will let you sell ALL items you have, well\n" +
        "                at least the droppable, and no coins.\n" +
        "    sell sword, sell second sword, sell sword 2, sell two swords\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too. \n" +
        "                I sell only one item at a time, though! \n" +
        "    If you want a list of all swords available in the store, the\n" +
        "    correct syntax is: list swords\n" +
        "                'list weapons', 'list armours' also works.\n";
}

/* Ashlar, 20 Jul 97 */
/*
 * Louie April 2006 - Set greed to 100.
 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include "/sys/money.h"
#include <macros.h>

inherit INNER_IN;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM    NINNER + "wshop_store"

void
create_neraka_room()
{
	set_short("inside the Neraka Weapon Emporium");
    set_long("You have entered a small shop housed in a low stone building. " +
        "There are shelves along the walls and a bench stands against one " +
        "wall, bearing a sign. An oil lamp is mounted on the wall, " +
        "illuminating the room. There is a doorway leading west out " +
        "of the shop. A banner on one wall proclaims this to be " +
        "'Neraka Weapon Emporium'.\n");

    add_item_inside();
    add_item(({"shelf","shelves"}),"Shelves line the walls, filled with " +
        "various pieces of weaponry.\n");
    add_item("bench","The bench stands against one wall. A large sign rests " +
        "on top of the bench, against the wall.\n");
    add_item(({"lamp","oil lamp"}),"The lamp sheds some light in the room, " +
        "enough to read by.\n");
    add_item("doorway","The doorway leads west, out of the shop.\n");

    add_item("sign", "It is a sign of instructions.\n");
    add_cmd_item("sign", "read", "@@do_read");

    add_exit(NINNER + "r27","west","@@msg");

    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);

    set_store_room(STORE_ROOM);
}

int
msg()
{
    write("You leave the shop and exit onto the street.\n");
    return 0;
}

void
init()
{
	::init();
    init_shop();
}

int
do_buy(string str)
{
    if (check_cheater(TP))
        return 1;
    return ::do_buy(str);
}

int
do_sell(string str)
{
    if (check_cheater(TP))
        return 1;
    return ::do_sell(str);
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  The shop will only buy armours
 * Argument:	  ob - The object player wants to sell
 * Returns:	      1 if the object was armour
 */
int
shop_hook_allow_sell(object ob)
{
    /* weapon_filter() is defined in /lib/shop */
    return weapon_filter(ob);
}

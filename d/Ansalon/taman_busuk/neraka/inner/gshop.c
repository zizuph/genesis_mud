/* Ashlar, 5 Jul 97 */
/*
 * Louie April 2006 - Changed to 100 greed.
 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include "/sys/money.h"
#include <macros.h>

inherit INNER_IN;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM    NINNER + "gshop_store"

void
create_neraka_room()
{
	set_short("inside Neraka General Store");
    set_long("You have entered a small shop housed in a low stone building. " +
        "There are shelves along the walls and a bench stands against one " +
        "wall, bearing a sign. An oil lamp is mounted on the wall, " +
        "illuminating the room. There is a doorway leading east out " +
        "of the shop. A banner on one wall proclaims this to be " +
        "'Neraka General Store'.\n");

    add_item_inside();
    add_item(({"shelf","shelves"}),"Shelves line the walls, filled with " +
        "various items.\n");
    add_item("bench","The bench stands against one wall. A large sign rests " +
        "on top of the bench, against the wall.\n");
    add_item(({"lamp","oil lamp"}),"The lamp sheds some light in the room, " +
        "enough to read by.\n");
    add_item("doorway","The doorway leads east, out of the shop.\n");

    add_item("sign", "It is a sign of instructions.\n");
    add_cmd_item("sign", "read", "@@do_read");

    add_exit(NINNER + "r8","east","@@msg");
    //add_exit(STORE_ROOM, "east","@@wiz_check",1,1);

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
    write("You are not allowed inside the storeroom.\n");
    say(QCTNAME(this_player()) + " tries to go east but fails.\n");
    return 1;
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  The shop will not buy high class armours or weapons
 * Argument:	  ob - The object player wants to sell
 * Returns:	      1 if the object was neither high class armour or weapon
 */
int
shop_hook_allow_sell(object ob)
{
    /* weapon_filter() and armour_filer() are defined in /lib/shop */
    return !((weapon_filter(ob) && ((ob->query_hit() + ob->query_pen()) > 30)) ||
        (armour_filter(ob) && (ob->query_ac() > 15)));
}

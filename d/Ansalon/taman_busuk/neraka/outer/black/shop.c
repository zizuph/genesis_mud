/* Ashlar, 8 Jun 97 */
/*
 * Louie April 2006 - set greed to 100.
 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include "/sys/money.h"
#include <macros.h>

inherit OUTER_IN;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM    NOUTER + "black/shop_store"

void
create_neraka_room()
{
	set_short("inside a dark shop");
    set_long("You are inside a dark shop in the Black Quarter. A table " +
        "stands in one end of the room, with a sign propped against it. " +
        "Behind the table is an exit to the store room. The store looks " +
        "rather shabby and it doesn't seem to get much trade.\n");

    add_item_inside();
    add_item("table","It is a worn, dusty table, with a sign propped against " +
        "it.\n");
    add_item("store room","You cannot see much of the store room, it is even " +
        "darker in there.\n");
    add_item("exit","There is an exit to the east, leading to the store room.\n");

    add_item("sign", "It is a sign of instructions.\n");
    add_cmd_item("sign", "read", "@@do_read");

    add_exit(NOUTER+"black/b13","out","@@msg");
    add_exit(STORE_ROOM, "east","@@wiz_check",1,1);

    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);

    set_store_room(STORE_ROOM);
}

int
msg()
{
    write("You leave the dark store.\n");
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


/* Ashlar, 18 May 97 */
/*
 * Louie April 2006 - Set greed to 100.
 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include "/sys/money.h"
#include <macros.h>

inherit OUTER_IN;
inherit "/lib/shop";

#define STORE_ROOM    NOUTER + "blue/shop_store"

void
create_neraka_room()
{
	set_short("inside a small store");
    set_long("You have entered a small store in the Blue Quarter. A " +
        "sign hangs on the east wall, and a curtain on the south wall " +
        "leads into the storeroom.\n");

    add_item_inside();
    remove_item("east wall");
    add_item("east wall","A sign hangs on the east wall, with instructions " +
        "on how to use the shop.\n");
    remove_item("south wall");
    add_item("south wall","A curtain on the south wall leads into the " +
        "storeroom.\n");
    remove_item("walls");
    add_item("walls","A sign hangs on the east wall, and a curtain on " +
        "the south wall.\n");

    add_item("curtain","It leads into the storeroom.\n");
    add_item("storeroom","You cannot see the storeroom from here.\n");

    add_item("sign", "It is a sign of instructions.\n");
    add_cmd_item("sign", "read", "@@do_read");

    add_exit(NOUTER+"blue/b13","out","@@msg");
    add_exit(STORE_ROOM, "south","@@wiz_check",1,1);

    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);

    set_store_room(STORE_ROOM);
}

int
msg()
{
    write("You leave the cramped store.\n");
    return 0;
}

void
init()
{
	::init();
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
    if (this_player()->query_wiz_level())
        return 0;
    write("You are not allowed inside the storeroom.\n");
    say(QCTNAME(this_player()) + " tries to go south but fails.\n");
    return 1;
}


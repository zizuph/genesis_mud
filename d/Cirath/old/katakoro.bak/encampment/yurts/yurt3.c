/* Shop Yurt, Yurt3.c
 * Chaos, 5 April 1995
 *
 * Made from;
 * /d/Genesis/doc/examples/trade/shop.c
 * Mercade, 7 January 1994
 */

inherit "/std/room";
inherit "/lib/shop";

#include <macros.h>
#include <stdproperties.h>

#define STORE  "/d/Cirath/katakoro/encampment/yurts/yurtstore"
#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
    set_short("A merchants yurt");
    set_long("This yurt is owned by a merchant not of the barbarian " +
	"tribes.  He has set up here to provide an outlet for the "+
	"items aquired by the raiders.  Though not very profitable for "+
   "merchant, it does provide some trade for the barbarians.  "+
        "There is an exit to the north which looks like it leads "+
	"to a storeroom of sorts.  The only other exit is out the "+
	"entrance.  There is a poster hanging from the wall with "+
	"instructions on it.\n");

    add_item("yurt","This yurt has been kept very clean.  The thick "+
	"felt carpet on the floor shows little sign of wear, and "+
	"there is no sign of dirt.  All equipment for sale is kept "+
	"in a storeroom and so there is nothing around to clutter "+
	"up the shop.\n");

   add_item("poster","You may 'list', 'buy', or 'sell' items here.\n");

    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    add_prop(ROOM_I_INSIDE,1);

    add_exit(PATH+"encampment/camp4","out");
    add_exit(STORE,"north", "@@check_wizard");
}

void
init()
{
    ::init();
    init_shop();
}

int
check_wizard()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    write("The merchant blocks your way and asks if you wish to make "+
	"a purchase.\n");
    say(QCTNAME(this_player()) + " is blocked by the merchant.\n");
    return 1;
}


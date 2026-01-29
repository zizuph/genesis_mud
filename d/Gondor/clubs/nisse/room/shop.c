/*
 *  /d/Gondor/clubs/nisse/room/shop.c
 *
 *  The shop in the Nisse Ohtar camp.
 *
 *  Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

#define STORE_ROOM "/d/Gondor/clubs/nisse/room/store"

/*
 *  Prototypes
 */
void	create_shop();
string	exa_poster();

void
create_shop()
{
    ::create_shop();

    set_short("the shop of the Nisse Ohtar");
    set_long("This is the local shop for the Nisse Ohtar. The tinker will " +
        "be more than happy to buy your wares or sell to you. She does " +
        "not really care where you found your equipment and is very " +
        "discreet when it comes to items that have been acquired in " +
        "unusual places. There is a counter where items for sale are " +
        "displayed. You can read the poster for instructions. The exit " +
        "from the shop leads out.\n");

    add_item(({"counter"}),
        "Items for sale are on display in a wooden counter with a glass " +
        "front. You can look but do not touch.\n");

    set_shop_name("The Nisse Ohtar Shop");
    set_store_room(STORE_ROOM);

    set_keeper_file(NISSE_NPC_DIR + "tinker");

    add_prop(ROOM_I_INSIDE, 1);

    add_item("poster", "It has readable words on it.\n");

    add_exit(NISSE_ROOM_DIR + "path1", "out", 0, 0, 0);
}

/*
 *  Function name: exa_poster
 *  Description  : It's called when a player examines a poster.
 *  Returns      : string with the text on a poster
 */
string
exa_poster()
{
    return "\nWelcome to the Nisse Ohtar shop!\n" +
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
        "                'value' or 'buy' too. Beware, you will never buy\n" +
        "                more than one item at a time. So if you really\n" +
        "                want those three expensive swords, you have to \n" +
        "                repeat yourself three times.\n" +
        "    If you want a list of all swords available in the store, the\n" +
        "    correct syntax is: list swords\n" +
        "                'list weapons', 'list armours' also works.\n\n";
}

/*
 *  Function name: shop_hook_filter_sell
 *  Description  : This function should guarantee this shop trades with
 *                 all kinds of the goods.
 *  Arguments    : object x - an object to sell
 *  Returns      : always 0
 */
public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}

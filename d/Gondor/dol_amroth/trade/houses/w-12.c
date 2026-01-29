/* -*- Mode: C -*-
 *
 * trade/houses/w-12.c
 *
 * Skippern 20(c)01
 *
 * A small shop in Dol Amroth.
 */
#include "../../defs.h"

inherit "/d/Gondor/common/lib/shop";

#include <macros.h>

/* Prototypes */

void
create_shop()
{
    set_short("inside a shop");
    set_long("This is inside a small shop in Dol Amroth, a large counter " +
	     "devides the room in two, and on the other side a shop " +
	     "keeper stands.\n");

    set_store_room(DOL_OTHER + "store/w-12");
    set_keeper_file(DOL_NPC + "keeper/w-12");
    set_shop_name("Dol Amroth Junk Yard");
    set_hated_race( ({ "gnome" }) );
    set_suspected_race( ({ "goblin" }) );
    set_favoured_race( ({ "human" }) );

    clone_object(DOL_OBJ + "doors/w-12-door")->move(this_object());
}

void
init()
{
    ::init();
    init_shop();
}

public void
shop_hook_list_empty_store(string str)
{
    NF("The shopkeeper says: I do not sell my goods here, find yourself " +
        "another shop.\n");
}

public void
shop_hook_list_no_match(string str)
{
    NF("The shopkeeper says: I do not sell my goods here, find yourself " +
        "another shop.\n");
}

public void
shop_hook_buy_no_match(string str)
{
    NF("The shopkeeper says: I do not sell my goods here, find yourself " +
        "another shop.\n");
}

public mixed
shop_hook_filter_sell(object o)
{
    return 0;
}


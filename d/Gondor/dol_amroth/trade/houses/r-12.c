/* -*- Mode: C -*-
 *
 * trade/houses/o-11.c
 *
 * Skippern 20(c)01
 *
 * A small shop in Dol Amroth.
 */
#include "../../defs.h"

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/potion_shop";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

static object ShopKeeper;
/* Prototypes */



void
create_room()
{
    set_short("inside a shop");
    set_long("This is inside a small shop in Dol Amroth, a large counter " +
	     "devides the room in two, and on the other side a shop " +
	     "keeper stands. On small shelves all over the walls, small " +
	     "bottles store many sorts of drugs and potions.\n");

    config_default_trade();
    set_money_greed_buy(55);
    set_money_greed_sell(145);

    set_store_room(DOL_OTHER + "store/r-12");
    call_other(store_room, "load_me");
    /*
    set_keeper_file(DOL_NPC + "keeper/r-12");
    set_shop_name("Dol Amroth Potions and Antidotes");
    set_hated_race( ({ "goblin" }) );
    set_suspected_race( ({ "gnome", "hobbit" }) );
    set_favoured_race( ({ "human", "elf" }) );
    */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    clone_object(DOL_OBJ + "doors/r-12-door")->move(this_object());
    reset_room();
}

void
reset_room()
{
    ::reset_room();
    if (!present(ShopKeeper))
    {
	ShopKeeper = clone_object(DOL_NPC + "keeper/r-12");
	ShopKeeper->move(this_object());
    }
}

void
init()
{
    ::init();
    init_potion_shop();
}


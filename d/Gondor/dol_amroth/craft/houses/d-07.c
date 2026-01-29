/*
 * craft/houses/d-07.c
 *
 * Skippern 20(c)01
 *
 * An armour shop in Dol Amroth.
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

    set_store_room(DOL_OTHER + "store/d-07");
    set_keeper_file(DOL_NPC + "keeper/d-07");
    set_shop_name("Dol Amroth Armour Smith");
    set_hated_race( ({ }) );
    set_suspected_race( ({ "gnome", "goblin" }) );
    set_favoured_race( ({ "human" }) );

    clone_object(DOL_OBJ + "doors/d-07-door")->move(this_object());
}

void
init()
{
    ::init();
    init_shop();
}


mixed
shop_hook_filter_sell(object x)
{
    if (!armour_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n"+
	    "The shopkeeper says: I do not trade in anything but " +
	    "armours!\n";
    else
        return 0;
}


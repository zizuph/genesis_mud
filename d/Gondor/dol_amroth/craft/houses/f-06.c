/*
 * craft/houses/f-06.c
 *
 * Skippern 20(c)01
 *
 * A small shop in Dol Amroth.
 */
#include "../../defs.h"

inherit "/d/Gondor/common/lib/shop";

#include <macros.h>

/* Prototypes */
int store();

void
create_shop()
{
    set_short("inside a shop");
    set_long("This is inside a small shop in Dol Amroth, a large counter " +
	     "divides the room in two, and on the other side a shop " +
	     "keeper stands.\n");

    set_store_room(DOL_OTHER + "store/f-06");
    set_keeper_file(DOL_NPC + "keeper/f-06");
    set_shop_name("Dol Amroth Weapon Smith");
    set_hated_race( ({ }) );
    set_suspected_race( ({ "gnome", "hobbit", "goblin" }) );
    set_favoured_race( ({ "human" }) );


    //    add_exit(DOL_OTHER + "store/o-11", "up", &store(), 1, 0);
    clone_object(DOL_OBJ + "doors/f-06-door")->move(this_object());
}

void
init()
{
    ::init();
    init_shop();
}

int
store()
{
    if (this_player()->query_wiz_level())
    {
	write("You jump over the counter and climbs up the ladder.\n");
	say(QCTNAME(this_player()) + " jumps over the counter and " +
	    "climbs up the ladder.\n", this_player());
	return 0;
    }
    write("The ladder is on the other side of the counter, you cannot " +
	  "pass.\n");
    return 1;
}

mixed
shop_hook_filter_sell(object x)
{
    if (!weapon_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n"+
            "The shopkeeper says: I do not trade in anything but " +
            "weapon!\n";
    else
        return 0;
}




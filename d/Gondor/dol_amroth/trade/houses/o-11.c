/* -*- Mode: C -*-
 *
 * trade/houses/o-11.c
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

    set_store_room(DOL_OTHER + "store/o-11");
    set_keeper_file(DOL_NPC + "keeper/o-11");
    set_shop_name("Dol Amroth General Store");
    set_hated_race( ({ "goblin" }) );
    set_suspected_race( ({ "gnome" }) );
    set_favoured_race( ({ "human" }) );

    clone_object(DOL_OBJ + "doors/o-11-door")->move(this_object());
}

void
init()
{
    ::init();
    init_shop();
}


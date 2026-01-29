/*
 * ship.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008.
 */

#pragma save_binary
#pragma strict_types

#include "../../defs.h"
#include <macros.h>
#include "/d/Genesis/ship_new/ships.h"

inherit STDSHIP;

void
create_ship()
{
    if (!IS_CLONE)
        return;

    ::create_ship();
    seteuid(getuid());
    set_cabin(SHIPDIR + "cadusparkle/cabin");
    set_deck(SHIPDIR + "cadusparkle/deck");
    set_name("ship");
    add_name("boat");
    add_name("warship");
    add_adj("huge");
    set_long("A huge warship that travels between Sparkle and Cadu to " +
             "protect the waters from fierce warriors.\n");

}

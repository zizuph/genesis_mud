/*
 * Store for Telberin
 * Coded by Finwe, January 1997
 * Recoded by Shiva, October 1998
 */
 
#include "defs.h"

inherit TELBERIN_ROOM;
inherit "/lib/store_support";

#include <stdproperties.h>

void
create_telberin_room()
{
    set_short("Stuffy store room");
    set_em_long("You are in the stuffy store room of the general store.\n");
 
    set_max_values(30, 5);
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit("shop", "down");
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

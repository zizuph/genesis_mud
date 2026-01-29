/*
 * Store for Telberin
 * Coded by Finwe
 * January 1997
 */
 
inherit "/std/room";
inherit "/lib/store_support";
 
#include "default.h"  
#include "/d/Emerald/defs.h"
 
int reset_room()
{
}
 
void
create_room()
{
    set_short("Stuffy store room");
    set_long("You are in the stuffy store room of the general store.\n");
 
    set_max_values(30, 5);
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(THIS_DIR + "shop", "down", 0);
    reset_room();
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

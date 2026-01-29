/*
 * Storeroom of Keepers shop
 * Coded by Finwe
 * January 1997
 * --used by Alaron (with modifications for Keepers)
 */
 
inherit "/std/room";
inherit "/lib/store_support";
 
#include <stdproperties.h>
 
void
create_room()
{
    set_short("Small clean store room");
    set_long("You are in a small store room behind the Keepers shop.\n");
 
    set_max_values(30, 5);
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit("shop", "south");
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


/* 
 *  Inherit this into the pier at which your ship starts if you want 
 *  the ship to be able to go idle. 
 *  Remember to call set_ship(ship object) in your create_room() function. 
 *
 *  Maniac, June 1997
 */ 

#pragma strict_types
#pragma save_binary

inherit "/std/room"; 

#include <filter_funs.h>

object associated_ship; 

public void
set_ship(object ship)
{
    associated_ship = ship; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (interactive(ob) && objectp(associated_ship)) 
        associated_ship->start_ship(); 
}

public int
query_players_present()
{
    return sizeof(FILTER_PLAYERS(all_inventory(this_object()))); 
}


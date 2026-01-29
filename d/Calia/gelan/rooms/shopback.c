/*
 * Coder : Maniac
 *
 * This is the store-room of Coiney Miser, in the town of Gelan 
 * Created 7/94 by Maniac
 *
 * Revision history:
 */


#pragma save_binary

inherit "/lib/store_support";
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "room.h"
#include GUARD_INCLUDE

#define SHOP            (GELAN_ROOMS +  "shop")



void
create_room() 
{
    set_short("the store-room of the shop in Gelan");
    set_long("This store-room is used to store all items that are " +
             "for sale in Coiney Miser's shop in Gelan.\n"); 

    add_exit(SHOP, "down");

    add_prop(ROOM_I_INSIDE, 1);

}



public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}


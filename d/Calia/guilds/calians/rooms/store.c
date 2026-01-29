/*
 *   The storage room of the example shop
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room() 
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
   
   add_exit(ROOM("light_shop"), "southeast");
   
   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
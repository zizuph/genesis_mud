/*
 *   The storage room of the Gondorian Rangers shop
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

#include "../merc.h"

void    reset_room();

object *oil;
int nr;

void
create_room() 
{
   set_short("The store-room");
   set_long("This is the store-room for the Mercenary camp Store.\n");

   add_exit("shop", "south",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   nr = 3 + random(4);
   oil = allocate(nr);
   reset_room();
}

void
reset_room()
{
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  store_update(obj);
}

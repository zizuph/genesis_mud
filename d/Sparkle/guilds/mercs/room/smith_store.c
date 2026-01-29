
#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

#include "../merc.h"
#include "room.h"

void
create_room() 
{
   set_short("The store room");
   set_long("This is the store room of the smith shop.\n");

   add_exit(MROOM + "smith", "out",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   reset_room();
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  store_update(obj);
}

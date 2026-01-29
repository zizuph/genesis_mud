/*
 *   The storage room of the Minas Tirith shop
 */

inherit "/d/Gondor/common/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototype */
void reset_room();

int nr;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() 
{
   set_short("The store room of Minas Tirith Arms Shoppe");
   set_long("This is the store room for the Minas Tirith Arms Shoppe.\n");

   add_exit("/d/Gondor/minas/rooms/mtarms", "east",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   reset_room();
}

void
reset_room()
{
  int i;

}


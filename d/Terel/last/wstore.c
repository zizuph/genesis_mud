/*
 *   The storage room of the Last shop
 */

inherit "/d/Terel/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

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
   set_short("The store room of Last Arms Shoppe");
   set_long("This is the store room for the Last Arms Shoppe.\n");


   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   reset_room();
}

void
reset_room()
{
  int i;

}

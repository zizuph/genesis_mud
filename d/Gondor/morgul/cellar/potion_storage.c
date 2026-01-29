/*
 *   The storage room of the potion shop.
 *   Original by Falke; rehacked by Laurelin.
 *
 *   Mopdified for Minas Morgul in Gondor@Genesis by Olorin.
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/potion_storage";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MORGUL_POTION_SHOP	"/d/Gondor/morgul/cellar/potion_shop"
#define MORGUL_POTION_SAVE	"/d/Gondor/morgul/cellar/potion_store"

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the potion shop in Minas Morgul.\n");

   add_exit(MORGUL_POTION_SHOP, "out");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   set_save_file(MORGUL_POTION_SAVE);
   create_potion_storage();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   enter_storage_inv(ob, from);
}


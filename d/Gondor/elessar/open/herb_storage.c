/*
 *   The storage room of the herb shop.
 *   Original by Falke; rehacked by Laurelin.
 *
 *   Mopdified for Minas Morgul in Gondor@Genesis by Olorin.
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herb_storage";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define TIRITH_HERB_SHOP	"/d/Gondor/minas/rooms/herb_shop"
#define TIRITH_HERB_SAVE	"/d/Gondor/minas/rooms/herb_store"

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the herb shop in Minas Tirith.\n");

   /* set max # of obs in store and max # of identical obs */
   set_max_values( 100, 10);

   add_exit(TIRITH_HERB_SHOP, "out");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   set_save_file(TIRITH_HERB_SAVE);
   if (file_size(save_file + ".o") >= 0)
       restore_object(save_file);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    enter_storage_inv(ob, from);
}


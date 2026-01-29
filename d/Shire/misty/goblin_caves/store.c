/* The storage room of the Shop in Goblin caves */

inherit "/lib/store_support";
#include "../local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(CAVE_DIR + "shop", "east");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

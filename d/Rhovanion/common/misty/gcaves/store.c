/* The storage room of the Shop in Goblin caves */

inherit "/std/room";
inherit "/lib/store_support";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_room()
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

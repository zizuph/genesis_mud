/*
 *   The storage room of the Last shop
 */

inherit "/d/Terel/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() 
{
   set_short("The store room of Amaylin's Weapon shop");
   set_long("This is the store room for Amaylin's weapon shop.\n");


   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    set_default_stock(({CALATHIN_DIR + "weapon/shortsword", 3,
        CALATHIN_DIR + "weapon/twohand", 1,
        CALATHIN_DIR + "weapon/battleaxe",2,
        CALATHIN_DIR + "weapon/mace",3}));
   reset_store();
}

void
reset_room()
{
    reset_store();
}

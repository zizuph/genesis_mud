/*
 *   The storage room of the example shop
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";

#include <stdproperties.h>


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


public void
create_room() 
{
    set_short("Gem Store Room");
    set_long("Gem shop store room.\n");

    add_exit(CALATHIN_DIR + "gem_shop", "down");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    set_default_stock(({
        "/d/Genesis/gems/obj/sapphire",5,
         "/d/Genesis/gems/obj/bloodstone",4,
        "/d/Genesis/gems/obj/diamond",2}));
    reset_store();
}

void
reset_room()
{
    reset_store();
}

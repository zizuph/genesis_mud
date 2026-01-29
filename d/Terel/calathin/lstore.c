/*
 *   The storage room of the Calathin Armour Shop
 */

inherit "/d/Terel/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"
#define GON_LAMP "/d/Gondor/common/obj/oil_lamp"
#define GON_FLASK "/d/Gondor/common/obj/oilflask"

/* prototype */



public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() 
{
    set_short("The store room of Lamp Shop");
    set_long("This is the store room for the Lamp Shop.\n");
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    set_default_stock(({ 
        GON_LAMP, 5,
        GON_FLASK, 8,
        CALATHIN_DIR + "obj/ltorch",8}));

    reset_store();
}

void reset_room()
{
    reset_store();
}

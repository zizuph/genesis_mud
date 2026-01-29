/*
 *   The storage room of the Calathin Meat Shop
 */

inherit "/d/Terel/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

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
    set_short("The store room of Sturdy Shield Armour Shop");
    set_long("This is the store room for the Sturdy Shield Armour Shop.\n");
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    reset_store();
}

void reset_room()
{
    reset_store();
}

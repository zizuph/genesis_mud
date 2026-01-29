/*
 *   The storage room of the Calathin Armour Shop
 */

inherit "/d/Terel/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

#define SHIRE_IRBAR "/d/Shire/guild/smiths/obj/ir_bar.c"

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

    set_default_stock(({ 
        MANSION +"obj/mining_boots",3,
        SHIRE_IRBAR, 100,
        CALATHIN_DIR + "armour/stud_armour",3 }));

    reset_store();
}

void reset_room()
{
    reset_store();
}

/*
 * Store room of Shop of Green Oaks
 * By Finwe, March 2005
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;
inherit "/lib/store_support";

#define SHIRE_DIR   "/d/Shire/"
void
create_indoor_room()
{
    set_short("This is the Store room of the Shop of Green Oaks");
    set_long("If you're here, you got here with the help of a wizard. " +
        "This room is completely closed off.\n");

    set_max_values(50, 7);
    set_default_stock( ({SHIRE_DIR + "common/obj/shoptorch", 3,
        SHIRE_DIR + "common/weapon/shopsword", 5}));
    reset_store();
    reset_room();
    add_exit(GO_DIR + "shop", "out");
}

void reset_room() 
{ 

}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

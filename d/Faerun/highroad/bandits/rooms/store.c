/*
 * store room for Bandits
 * By Finwe, September 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <const.h>

inherit "/std/room";
inherit "/lib/store_support";

void
create_room()
{
    set_short("Store room for bandits");
    set_long(short() + ". Only wizards can come here.\n");
    add_exit("shop", "out");

    set_default_stock( ({"/d/Sparkle/area/faerie/wep/ch_lsword", 2,
        "/d/Sparkle/area/faerie/wep/ch_dagger", 2,
        "/d/Sparkle/area/faerie/wep/ch_club", 2,
        "/d/Sparkle/area/faerie/wep/ch_baxe", 2,
        "/d/Sparkle/area/faerie/arm/ch_pmail", 2,
        "/d/Sparkle/area/faerie/arm/ch_helm", 2,
        "/d/Sparkle/area/faerie/arm/ch_bracers", 2 }));

    reset_room();

}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();

}


reset_room() 
{
    reset_store();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


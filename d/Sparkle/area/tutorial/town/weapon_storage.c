/*
 *  /d/Sparkle/area/tutorial/silverdell/weapon_storage.c
 *
 *  The storage room of the Silverdell Weapon Shop.
 *
 *  Supports store file:
 *    /d/Genesis/login/new/silverdell/rooms/weapon_shop.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/lib/store_support";

#include <stdproperties.h>

/* prototypes */
public void        reset_room();


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell() 
{
    set_short("the store room of the Weapon Shop of Silverdell");
    set_long("This is the store room for the Weapon Shop of Silverdell.\n");

    add_exit("weapon_shop", "west");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    set_default_stock( ({
        WEP_DIR + "shop_club1", 4,
        WEP_DIR + "shop_club2", 3,
        WEP_DIR + "shop_knife1", 4,
        WEP_DIR + "shop_knife2", 3,
        WEP_DIR + "shop_axe1", 4,
        WEP_DIR + "shop_axe2", 3,
        WEP_DIR + "shop_sword1", 4,
        WEP_DIR + "shop_sword2", 3, }) );

    reset_room();
} /* silverdell_room */


/*
 * Function name:        reset_room
 * Description  :        make sure the store room has
 *                       adequate supplies
 */
public void
reset_room()
{
    reset_store();
} /* reset_room */

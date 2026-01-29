/*
 *  /d/Sparkle/area/tutorial/silverdell/armour_storage.c
 *
 *  The storage room of the Silverdell Armour Shop.
 *
 *  Supports store file:
 *    /d/Genesis/login/new/silverdell/rooms/armour_shop.c
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
    set_short("the store room of the Armour Shop of Silverdell");
    set_long("This is the store room for the Armour Shop of"
      + " Silverdell.\n");

    add_exit("armour_shop", "north");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    set_default_stock( ({
        ARM_DIR + "shop_helm1", 3,
        ARM_DIR + "shop_helm2", 1,
        ARM_DIR + "shop_vest1", 3,
        ARM_DIR + "shop_vest2", 1,
        ARM_DIR + "shop_bracers1", 3,
        ARM_DIR + "shop_bracers2", 1,
        ARM_DIR + "shop_greaves1", 3,
        ARM_DIR + "shop_greaves2", 1,
        ARM_DIR + "shop_shield", 3, }) );

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

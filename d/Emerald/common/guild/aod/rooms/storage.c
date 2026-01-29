/*
 *  /d/Emerald/common/guild/aod/rooms/storage.c
 *
 *  The storage room of the Army of Darkness shop.
 *
 *  Supports store file:
 *    /d/Emerald/common/guild/aod/rooms/aod_shop.c
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
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
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room() 
{
    set_short("the store room of the Army of Darkness shop");
    set_long("This is the store room for the Army of Darkness shop.\n");

    add_exit("aod_shop", "west");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    set_default_stock( ({
        AOD_ARM_DIR + "ogre_ring", 10,
        AOD_ARM_DIR + "ogre_necklace", 5,
        AOD_ARM_DIR + "ogre_cloak", 6,
        AOD_WEP_DIR + "shop_club1", 5,
        AOD_WEP_DIR + "shop_club2", 4,
        AOD_OBJ_DIR + "backpack", 5 }) );

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

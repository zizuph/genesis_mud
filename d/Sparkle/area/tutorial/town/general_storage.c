/*
 *  /d/Sparkle/area/tutorial/silverdell/general_storage.c
 *
 *  The storage room of the Silverdell General Store.
 *
 *  Supports store file:
 *    /d/Genesis/login/new/silverdell/rooms/general_store.c
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


/*
 * Function name:        enter_inv
 * Desciption   :        Remove any stuff we don't want cluttering up
 *                       the list. Update the display.
 * Arguments    :        object ob - the object sold,
 *                       object from - where it came from
 */
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
    set_short("the store room of the General Store of Silverdell");
    set_long("This is the store room for the General Store of"
      + " Silverdell.\n");

    add_exit("general_store", "west");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    set_default_stock( ({
        OBJ_DIR + "torch", 5,
        OBJ_DIR + "backpack", 5 }) );

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

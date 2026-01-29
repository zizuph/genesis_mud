/*
 *  /d/Sparkle/area/city/rooms/sparkle_room_base.c
 *
 *  This will be the base file for every room in new Sparkle
 *
 *  Adapted April 2008, by Petros, from outdoor_room.c
 */
#pragma strict_types

#include "../defs.h"
#include "/d/Sparkle/sys/defs.h"
#include <stdproperties.h>

inherit ROOMS_DIR + "delay_room";
inherit LIB_DIR + "random_noise";
inherit "/d/Sparkle/area/city/lib/broadcast_lib";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global Variables */

/* Prototypes */
nomask void        create_room();
public void        create_sparkle();
public string      sparkle_short();
public string      sparkle_long();
public int         try_item(mixed names, mixed desc);

/*
 * Function name:        create_room
 * Description  :        set up the room
 */
nomask void
create_room()
{
    // These calls should go before create_sparkle to allow
    // for child classes to just use set_short and set_long
    // if they choose to do so.
    set_short(sparkle_short);
    set_long(sparkle_long);

    add_prop("_room_s_mapfile", TEXT_DIR + "sparkle_main.txt");

    clear_broadcast_rooms();
    create_sparkle();

    reset_room();
} /* create_room */


/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_sparkle()
{
} /* create_sparkle */


/*
 * Function name:        sparkle_short
 * Description  :        provide a short description for street locations
 *                       in the City of Sparkle
 * Deturns      :        string -- the short description
 */
public string
sparkle_short()
{
    return "Please define sparkle_short()";
} /* sparkle_short */


/*
 * function name:        sparkle_long
 * description  :        provides a long descriptions for street locations
 *                       in the city of Sparkle
 * returns      :        the room description
 */
public varargs string
sparkle_long()
{
    return "Please define sparkle_long()\n";
} /* sparkle_long */

/*
 * Function name:       try_item
 * Description  :       checks to see if an item already exists
 *                      within a given object, and if it does not, it then
 *                      adds it as add_item() would.
 * Arguments    :       mixed names --  string or array of strings, the
 *                                      item name(s).
 *                      mixed desc -- string or function, the description.
 * Returns      :       int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         i;
    string      *exists;

    if (pointerp(names)) 
    { 
        exists = ({});
        foreach (string name : names)
        {
            if (item_id(name)) 
            {
                exists += ({ name });
            }
        }
        names -= exists;
        if (sizeof(names))
        {
            add_item(names, desc);
        }
        i = sizeof(names);
    } 
    else if (!this_object()->item_id(names))
    {
        add_item(names, desc);
        i = 1;
    }
    return i;   // # of items added
}

/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this room. We want
 *                       to allow for broadcasting movement to rooms that
 *                       look onto this location.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
        send_debug_message("broadcast", "Entering environment "
            + file_name(this_object()));
        BC_MODULE->broadcast_movement(ob, this_object(), 1,
            from->query_broadcast_rooms());
    }
} /* enter_inv */


/*
 * Function name:        leave_inv
 * Description  :        Called when objects leave this room. We want
 *                       to allow for broadcasting movement to rooms that
 *                       look onto this location.
 * Arguments    :        ob: The object that just left this inventory
 *                       to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    if (living(ob))
    {
        send_debug_message("broadcast", "Leaving environment "
            + file_name(this_object()));
        BC_MODULE->broadcast_movement(ob, this_object(), 0);
    }

    ::leave_inv(ob, to);
} /* leave_inv */


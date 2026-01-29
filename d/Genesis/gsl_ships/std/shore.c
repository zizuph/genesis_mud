/*
 * Standard shore
 * TAPAKAH, 2008
 */

#include "../ships.h"

inherit "/std/room";
inherit LIBSHORE;

/*
 * Function:    create_shore
 * Description: Override this to declare your customizations for
 *              a shore room.
 */
public void
create_shore ()
{
}

public void
create_room()
{
    set_short("A shore room");
    set_long("A shore stretch along the body of water.\n");

    add_item(({ "sea", "water" }), 
        "The water splashes against the shore.\n");

    create_shore();
    initialize_shore();    
}

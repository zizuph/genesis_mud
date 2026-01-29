/*
 * File         : /d/Genesis/new/start/goblin/town/well.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 13, 1999
 * Modifications: 
 * Purpose      : The top of the oasis well
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>

public string bucket_desc();

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are at the oasis well");

    set_long("You are at the oasis well.\n" +
    "This must be where the goblins retrieve the water which they " +
    "sell at the bazaar.\n");

    add_item(({"well", "oasis well"}),
    "The well is in fine condition. A heavy limestone fortification " +
    "surrounds the dark opening. " + bucket_desc() + "There is a " +
    "small control panel here.\n");

    add_item(({"panel", "control panel", "lever"}),
    "The control panel is carved completely from stone. It has one " +
    "lever.");
}

public string
bucket_desc()
{
    return "A large bucket hangs out over the water.";
}
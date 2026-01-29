/*
 * File         : /d/Genesis/new/start/goblin/town/testing_place1.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : The Kalerian Ceremonial Testing Place
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are in a dark tunnel");

    set_long("You are in a dark tunnel.\n" +
    "The walls here are dimly lit by a soft, green glow.\n");

    add_item(({"glow", "green glow", "walls", "tunnel walls"}),
    "The walls are covered with tiny, worm-like creatures. Their " +
    "bodies give off a faint, green glow, illuminating the way " +
    "through here.\n");

    add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
    "The tiny, glowing worms slither blindly about on the rock walls.\n");

    add_exit("cavern_c2", "up");
}

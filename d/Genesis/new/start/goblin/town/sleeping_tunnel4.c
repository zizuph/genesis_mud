/*
 * File         : /d/Genesis/new/start/goblin/town/sleeping_tunnel4.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 13, 1999
 * Modifications: 
 * Purpose      : Tunnel from sleeping cell to Kalerus
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
    set_short("You are on a landing in a dark tunnel");

    set_long("You are on a landing in a dark tunnel.\n" +
    "The walls here are dimly lit by a soft, green glow. The stairs " +
    "make a sharp turn here, leading up to the east and down to the north.\n");

    add_item(({"glow", "green glow", "walls", "tunnel walls"}),
    "The walls are covered with tiny, worm-like creatures. Their " +
    "bodies give off a faint, green glow, illuminating the way " +
    "through here.\n");

    add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
    "The tiny, glowing worms slither blindly about on the rock " +
    "walls.\n");

    add_item(({"stairs", "stairway"}),
    "The stairs appear to have been hand carved right into the " +
    "original rock. It looks like a lot of work.\n");

    add_item(({"rock", "tunnel"}),
    "The tunnel appears to have been carved from the rock. It " +
    "must have taken many years.\n");

    add_item(({"landing"}),
    "This is a simple landing where the tunnel turns sharply east " +
    "as it continues up.\n");

    add_exit("sleeping_tunnel5", "north");
    add_exit("sleeping_tunnel3", "east");
}

/*
 * File         : /d/Genesis/new/start/goblin/town/river_tunnel3.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 13, 1999
 * Modifications: 
 * Purpose      : Tunnel from Kalerus to oasis well
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
   set_short("You are on a narrow walkway in a dark tunnel");

   set_long("You are on a narrow walkway in a dark tunnel.\n" +
   "The walls here are dimly lit by a soft, green glow. Below " +
   "you, a river rushes past, heading south.\n");

   add_item(({"glow", "green glow", "walls", "tunnel walls"}),
   "The walls are covered with tiny, worm-like creatures. Their " +
   "bodies give off a faint, green glow, illuminating the way " +
   "through here.\n");

   add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
   "The tiny, glowing worms slither blindly about on the rock walls.\n");

   add_exit("river_tunnel2", "northwest");

   add_exit("river_tunnel4", "south");
}

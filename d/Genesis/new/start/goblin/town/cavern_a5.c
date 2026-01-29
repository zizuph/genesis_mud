/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_a5.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : "Outdoors" in the Kalerus cavern
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
   set_short("You are standing on a river bank");

   set_long("You are standing on a river bank.\n" +
   "The walls here are dimly lit by a soft, green glow.\n" +
   "Describe: walkway into tunnel.\n");

   add_item(({"glow", "green glow", "walls", "tunnel walls"}),
   "The walls are covered with tiny, worm-like creatures. Their " +
   "bodies give off a faint, green glow, illuminating the cavern " +
   "mist.\n");

   add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
   "The tiny, glowing worms slither blindly about on the rock walls.\n");

   add_exit("cavern_b5", "north");

   add_exit("river_tunnel1", "south");
}

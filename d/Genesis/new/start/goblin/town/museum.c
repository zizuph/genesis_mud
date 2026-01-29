/*
 * File         : /d/Genesis/new/start/goblin/town/museum.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : Kalerus Museum
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
   set_short("You are in the Kalerus Museum");

   set_long("You are in the Kalerus Museum.\n");

   add_exit("cavern_c3", "north");
}

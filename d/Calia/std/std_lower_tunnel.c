/* Standard lower tunnel, extracted from Amelia's tunnel code by Maniac. 

   History:
          
*/

#pragma save_binary

inherit "/std/room";
#include "/sys/stdproperties.h"

/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long)
{
    set_short("An underground tunnel");
    set_long("The tunnel is carved from solid granite.  It is dimly lit " +
             "by strange blue torches that are placed in sconces " +
             "on the walls every 10 feet or so.  The tunnel extends " +
             "forward, and it's difficult to estimate how far it goes.  "+
             extra_long);

    add_item((({"torch", "torches", "blue torches"})),
             ("The torch does not glow with ordinary fire, but "+
             "instead has a ball of glowing blue crystal at the end.\n"));
    add_item("sconces", "Sconces are torch-holders.:)\n");
    add_item((({"walls", "wall", "ceiling"})),
             ("The walls and ceiling are made from solid granite.\n"));

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
}


int
travel_tunnel()
{
    write("You walk for about a mile down the tunnel.\n");
    return 0;
}

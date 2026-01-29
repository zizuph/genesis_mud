/* Castle Gylar
 *
 *
 * Nerul 2021
 */
 
#include "../defs.h"
#include "../guild.h"
inherit STD_ROOM;


void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
    
    set_long("You stand in a long and wide hallway going in the north-south "
	    +"direction. Looking up and down in what is pretty much a pitch "
		+"black tunnel, the only things you can clearly make out are the "
		+"many balistrarias providing just enough light to enable navigation. "
		+"The light from the entrance to the north provides some sense of "
		+"direction, but not much else. Part from the balistraria to the "
		+"west, there is nothing but cold walls forcing your movement north "
		+"towards the entrance or south towards the unknown.\n");
		
    set_short("Inside the southwest part of the castle’s fortifications.");
    
    
   /* Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while also providing a bare minimum of illumination to unadjusted eyes.

Object: balistraria
A thin cross-shaped opening in the west wall. You imagine firing arrows or 
bolts through them without much risk of retaliation.  */
    
    add_exit(THEORDER_GUILD_DIR + "rooms/27", "north");
	add_exit(THEORDER_GUILD_DIR + "rooms/38t", "south");
}
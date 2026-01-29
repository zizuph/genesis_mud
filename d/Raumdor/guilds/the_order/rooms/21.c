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
    
    set_long("You stand in a long and wide hallway going in the "
	    +"north-south direction. Looking in either direction in "
		+"what is pretty much a pitch black tunnel, the only things you "
		+"can clearly make out are the many balistrarias providing just "
		+"enough light to enable navigation. The entrance to the west does "
		+"provide some additional light, but for some reason light seems "
		+"to dim faster than what you are used to here.\n");
		
    set_short("Inside the castle’s fortification, entrance.");
    
    
   /* Object: Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while provide a bare minimum of illumination to untrained eyes. */
    
    add_exit(THEORDER_GUILD_DIR + "rooms/12", "north");
    add_exit(MTRAIL_DIR + "drawbridge", "west");
	add_exit(THEORDER_GUILD_DIR + "rooms/27", "south");
}
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
		+"black tunnel, the only things you can clearly make out are the many "
		+"balistrarias providing just enough light to enable navigation. The "
		+"light from the entrance to the north provides some sense of "
		+"direction in what is otherwise very poor lighting "
		+"conditions. There is a door to the west and an opening to "
		+"the east. Limited sight prevents you from seeing further "
		+"though.\n");
		
    set_short("Inside the southwest part of the castle’s fortifications.");
    
    
   /* Object: door
An old rusty metal door inserted in the west wall.



Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while also providing a bare minimum of illumination to unadjusted eyes. */
    
    add_exit(THEORDER_GUILD_DIR + "rooms/21", "north");
    add_exit(THEORDER_GUILD_DIR + "rooms/e", "west");
	add_exit(THEORDER_GUILD_DIR + "rooms/33", "south");
	add_exit(THEORDER_GUILD_DIR + "rooms/j", "east");
}
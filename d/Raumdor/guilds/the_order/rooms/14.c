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
    
    set_long("You stand in what appears to be a great hall. You are pretty "
    +"sure it used to be a courtyard of sorts, but unlike other castles, "
    +"this courtyard has a roof. Looking at the craftsmanship of the "
    +"gigantic pillars you are fairly certain the roof wasn't part of the "
    +"original design. As you try to find your bearing in these deplorable "
    +"lighting conditions, you slowly start to realize you are in what can "
    +"only be the northwest corner. As you squint your eyes you can make "
    +"out some paintings hanging crookedly on the adjacent walls. You can "
    +"walk pretty much unobstructed in any direction towards the south and "
    +"east or proceed back into the corridor to the west.\n");
		
    set_short("Inside a dimly lit hall");
    
    
   /* Object: Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while provide a bare minimum of illumination to untrained eyes. */
    
    add_exit(THEORDER_GUILD_DIR + "rooms/13", "west");
    add_exit(THEORDER_GUILD_DIR + "rooms/15", "east");
    add_exit(THEORDER_GUILD_DIR + "rooms/22", "south");
}
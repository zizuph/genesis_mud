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
    
    set_long("Sitting behind a square wooden desk sits a what "
    +"looks to be a rather young man guarding the shelves behind "
    +"him. You can see all sorts of armours, weapons and "
    +"miscellaneous objects stacked pretty neatly and organized. "
    +"As you look more closely you realize there's a cloth hanging "
    +"just behind the shelves, hiding what can only be a storage "
    +"room. You're fairly sure the shopkeeper has little interest "
    +"in you exploring further. Obviously, you wisely decide not to.\n");
		
    set_short("A dark, small room and a shopkeeper");
    
    
   /* Object: Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while provide a bare minimum of illumination to untrained eyes. */
    
    add_exit(THEORDER_GUILD_DIR + "rooms/16", "west");
}
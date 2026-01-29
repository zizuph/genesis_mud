/* Castle Gylar
 *
 *
 * Nerul 2021
 */
 
#include "../defs.h"
#include "../guild.h"
inherit STD_ROOM;


/*
 * Function name: block_player
 * Description  : If a crew member is present, blocks entrance.
 */
public int
block_player()
{
    if (present("_theorder_knight"))
    {       
        write("The guarding death knight stops you from going that way!\n");
        return 1;
    }
    
    return 0;
}

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
    
    set_long("You stand in a long and wide T-intersection. Looking "
    +"in any direction is pretty much like staring into pitch "
    +"black tunnel, with the only things you can clearly make "
    +"out are the many balistrarias providing just "
    +"enough light to enable navigation.\n");
		
    set_short("Inside the castle’s fortification, corridor.");
    
    
   /* Object: Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while provide a bare minimum of illumination to untrained eyes. */

    add_npc("/d/Raumdor/common/npc/order_death_knight", 1);
    
    add_exit(THEORDER_GUILD_DIR + "rooms/8", "north", block_player);
    add_exit(THEORDER_GUILD_DIR + "rooms/13", "east");
	add_exit(THEORDER_GUILD_DIR + "rooms/21", "south");
}
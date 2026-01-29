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
    
    set_long("You stand in the corner where two long and wide hallways meet. "
	    +"One in going north direction, the other continues eastwards. "
		+"Looking up and down what is pretty much two pitch black tunnels, the "
		+"only things you can clearly make out are the many balistrarias "
		+"providing just enough light to enable navigation. Where the tunnels "
		+"meet you make out a narrow spiralling staircase leading upwards "
		+"inside one of the towers visible from the outside.\n");
		
    set_short("Southwest corner of the castle’s fortifications.");
    
    
   /* Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while also providing a bare minimum of illumination to unadjusted eyes.

Object: balistraria
A thin cross-shaped opening in the west wall. You imagine firing arrows or 
bolts through them without much risk of retaliation.  */

    add_npc("/d/Raumdor/common/npc/order_death_knight", 1);
    
    add_exit(THEORDER_GUILD_DIR + "rooms/33", "north");
	add_exit(THEORDER_GUILD_DIR + "rooms/39", "east", block_player);
	add_exit(THEORDER_GUILD_DIR + "rooms/blaph", "up", block_player);
}
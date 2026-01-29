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
    
    set_long("You stand in a corridor going in the east-west direction. "
    +"There is not much to see here, but you recognize the walls as "
    +"being made of stone. To the east you see a weak glimmer of "
    +"light through an opening, and you’re fairly sure you can make "
    +"it out of here going west.\n");
		
    set_short("Inside a dark corridor");
    
    
   /* Object: Object: balistrarias
Tiny slits in the west walls serving as a means of defending the castle 
from intruders while provide a bare minimum of illumination to untrained eyes. */
    
    add_exit(THEORDER_GUILD_DIR + "rooms/12", "west");
    add_exit(THEORDER_GUILD_DIR + "rooms/14", "east");
}
/* 
 * Entrance of the Dewar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
	
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Entrance to a cool dark cavern");
    set_long("These caverns are well made. Dwarven "
    +"hands have had a play in their creation. "
    +"Smooth walls, well lit by oil lanterns, high "
    +"vaulted ceilings and comfortable temperature "
    +"all make this a rather nice place. Sounds of "
    +"cursing in the distance and the stains of "
    +"blood contrast the other elements of this cavern.\n");
    
    
    add_exit(RDIR + "d1","north", "@@leave_dewar",0);
    add_exit(RDIR + "np1","south","@@outdewar",0);
    reset_pal_dewar_room();
    
}

public int
leave_dewar()
{
	if (file_size(LOG_DIR + "dewar") > 100000)
	rename(LOG_DIR + "dewar", LOG_DIR + "dewar.old");
	write_file(LOG_DIR + "dewar", ctime(time())
      + " " + this_player()->query_name() + " - with a stat average of: " + 
	  this_player()->query_average_stat() +" - entered the the dewar "
	  +"mines.\n");
}

public int
outdewar()
{
	write("You step out of the cool dark cavern and back into the "
	+"crisp refreshing air of the outdoors.\n");
	return 0;
}
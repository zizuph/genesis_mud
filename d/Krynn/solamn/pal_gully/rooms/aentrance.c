/* 
 * First Room of the Aghar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE; 


/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
	
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_gully_room()
{
    set_short("Entrance to an abandoned mine");
    set_long("Warm putrid air gusts out from this "
    +"abandoned mine. The stench is horrid. You can see mounds "
    +"of garbage and other refuse from where you are "
    +"standing. The floors are covered in filth and muck while "
    +"the walls are roughly hewn. The ceiling here is held "
    +"up by thick pieces of wood built into an archway. "
    +"Joyful noises and singing can be heard from up ahead. "
    +"The mine is lit with oil lanterns that have seen "
    +"better days.\n");
	
	add_item(({"arch", "archway", "wooden archway", "wooden arch"}),"Thick "
	+"pieces of wood bound together to create a supportive wooden arch "
	+"to keep the ceiling from caving in.\n");
        
    add_exit(RDIR + "a1","south","@@leave_aghar",0);
    add_exit(RDIR + "np1","north", "@@outaghar",0);
    reset_pal_gully_room();
    
}

public int
leave_aghar()
{
	if (file_size(LOG_DIR + "aghar") > 100000)
	rename(LOG_DIR + "aghar", LOG_DIR + "aghar.old");
	write_file(LOG_DIR + "aghar", ctime(time())
      + " " + this_player()->query_name() + " - with a stat average of: " + 
	  this_player()->query_average_stat() +" - entered the the aghar "
	  +"caverns.\n");
}

public int
outaghar()
{
	write("You step out of the warm putrid air of the abandoned mine and "
	+"back into the crisp refreshing air of the outdoors.\n");
	return 0;
}
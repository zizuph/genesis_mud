/* /d/Faerun/guilds/warlocks/rooms/mist.c
 *
 * Warlock-related room.
 *
 * Nerull, 2017
 *
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "defs.h";
#include "../guild.h";

inherit WARLOCK_STD_ROOM;


string entrance()
{
	return "You feel the outline of an entrance "
    +"to somewhere below with your feet, but "
    +"can't see anything due to the blanket of mist "
    +"that conceals it entirely.\n";
}


public int
into_shaft()
{
    write("\n\nYou decend into the darkness below...\n\n");

    return 0;
}


public int
out_of_mist()
{
    write("\n\nAs you leave the heavy mist, you slowly start to see the "
    +"contours of pebbles and rocks, and finally "
    +"the sea.\n\n");

    return 0;
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_LIGHT, 1);

    set_short("Somewhere in the heavy mist");
	
    set_long("The mist surrounds you like an impenetrable "
    +"barrier in all direction. It is by coincidence that "
    +"you sometimes can see beyond five feet from your current "
    +"location, and all the sounds are dimmed to mere "
    +"soft whispers and faint echoes. This area is obviously "
    +"magically concealed from the rest of the world for some "
    +"reason. The ground feels soft, even if you can't see your "
    +"own feet due to an extraordinary thick blanket of mist.\n");

    add_item(({"up", "ceiling", "roof"}),
        "You look up, but see nothing but more conceiling "
        +"mist. You believe you are outdoors though.\n");
		
	add_item(({"wall", "walls"}),
        "While you believe you are outdoors, the present mist "
        +"could just aswell act as conceiling walls.\n");
		
	add_item(({"entrance", "hole"}), entrance);
    
    add_item(({"mist", "heavy mist", "barrier", "blanket",
    "blanket of mist", "fog"}), "Your feet and all around you "
    +"is covered by heavy mist, preventing you from seeing "
    +"the ground and more than five feet in every other "
    +"direction. You think it's here for a reason.\n");
		
	add_item(({"floor", "ground", "soft ground"}),
        "You believe the ground consists of mold or some sort of "
        +"grass. You step around some, and locate something "
        +"resembling an entrance down with your feet.\n");
    
    // Entrance to the private guildhall
    add_exit(WARLOCK_ROOMS_DIR + "shaft1", "down", into_shaft , 0 , 1);
    add_exit("/d/Faerun/red_cliffs/rooms/islands/warlock_island", "leave", out_of_mist);
    
    reset_faerun_room();
}


void
reset_room()
{
}



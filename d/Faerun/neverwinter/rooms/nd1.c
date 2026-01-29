/*  /d/Faerun/neverwinter/rooms/nd1.c
*
*   By Thessius, 2020
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_NEWERW_INDOOR;


public int
block_check()
{      
    write("The iron gates are closed, preventing access to Neverdeath. "
	   +"There has been no talk of opening the way to Neverdeath as of "
	   +"yet.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" tries to go west, but realizes that the direction "
    +"is blocked.\n", this_player());
        
    return 1;
}

void
create_neverw_room()
{
    set_long("Inside the Neverdeath Gate.\n"
        +"Silence and darkness fills the tunnel. The weight of the gate "
		+"seems heavy in this dark and musty gateway. Several heavy iron "
		+"gates impale the ground in front of you, barring entrance to "
		+"the section of Neverwinter known only as Neverdeath. moans, "
		+"heavy with the stench of death, radiate from the opposite side "
		+"of the tunnel.\n");
    
    set_short("Inside the Neverdeath Gate");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
     add_item(({"walls", "wall"}),
        "The walls are jagged and roughed over, with dips and depressions"
        +" encapsulating your view.");

    add_item(({"tunnel"}),
        "This tunnel looks jagged as if something forced its way into sol"
        +"id rock.\n");

    add_item(({"floor", "ground"}),
        "The floor is full of pebbles, stones, and other debris from brea"
        +"kage that created it. You notice cracks by your feet.\n");

    add_item(({"air", "haze"}),
        "The air here reeks of death. A dark green haze seems to "
        +"surround all you see.\n");

    add_item(({"cracks", "dips", "depressions", "dip", "depression", "crack"}),
        "Cracks and divots scatter the floor, as if it has been worn down"
        +" over time.\n");
		
    add_item(({"gates"}),
        "The gates are made of a thick, enchanted heavy iron, and can "
		+"only be lifted by a lever atop the massive wall.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "n10.c", "north");
    add_exit(ROOM_DIR + "w1.c", "south", block_check);
}


void
reset_faerun_room()
{
    set_searched(0);
}
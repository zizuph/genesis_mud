inherit "/std/room";

#include "/d/Emerald/defs.h"

create_room()

{
    set_short("Gate");
    
    set_long("   Looming over you this gate leads into the maw ; " +
        "of this long abandoned fortified gate. \n\n"); 
    
    
    
    add_exit("", "north", 0, 2);
    add_exit("", "west", 0, 2);
    add_exit("", "south", 0, 2);
    
}

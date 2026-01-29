/* /d/Faerun/guilds/warlocks/rooms/shaft2.c
 *
 * Warlock-related room.
 *
 * Nerull, 2017
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

public int
into_cavity()
{
    write("\n\nYou climb down into a murky water infested "
    +"underground earth cavity.\n\n");

    return 0;
}


public int
into_shaft()
{
    write("\n\nYou climb further up into the darkness...\n\n");

    return 0;
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    set_short("In a dark vertical shaft");
    
    set_long("You are somewhere inside a dark vertical "
    +"shaft that seems to be rudely carved out by hand. Small "
    +"steps allow for access into the shaft above, and "
    +"down into some wet murky cavity. The shaft seems to be "
    +"magically supported by roots in order to prevent its "
    +"collapse.\n");

    add_item(({"up", "ceiling", "roof", "exit"}),
    "This shaft is vertical, and right above is another "
    +"part of the shaft.\n");
        
    add_item(({"wall", "walls"}),
    "The surrounding walls of the shaft consist of compressed "
    +"mold and magically enhanced roots that keeps its "
    +"integrity.\n");
    
    add_item(({"mold", "steps", "root", "roots"}),"The "
    +"roots here form a tunnel-like structure, acting as "
    +"both steps and supporting structure for the shaft that "
    +"keeps the soft walls from collapsing. The roots "
    +"appear to have been magically enchanted or formed.\n");
        
    add_item(({"floor", "ground", "soft ground"}),
        "There is no ground or floor in the shaft.\n");
    
    // Entrance to the private guildhall
    add_exit(WARLOCK_ROOMS_DIR + "shaft1", "up", into_shaft);
    add_exit(WARLOCK_ROOMS_DIR + "join", "down", into_cavity);
    
    reset_faerun_room();
}


void
reset_room()
{
}



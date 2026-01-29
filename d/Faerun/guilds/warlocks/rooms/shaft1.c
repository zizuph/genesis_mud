/* /d/Faerun/guilds/warlocks/rooms/shaft1.c
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
exit_shaft(string str)
{
    if (str == "shaft" || str == "hole" || str == "cave" || str == "tunnel" 
    || str == "the shaft" || str == "the hole" || str == "the tunnel")
    {   
        write("\n\nYou climb up and onto the mossy ground outside!\n\n");
        
        tell_room(WARLOCK_ROOMS_DIR + "shaft1", QCTNAME(this_player())
        + " exits the shaft!\n", this_player());
        
        tell_room(MROOM_DIR + "metrail4", QCTNAME(this_player())
        + " climbs in from below!\n", this_player());
        
        this_player()->move_living("M", MROOM_DIR + "metrail4", 1);
        return 1;
    }
 
    write("Leave/exit what? The shaft?\n");
    
    return 1;
}


public int
into_shaft()
{
    write("\n\nYou climb further down into the darkness...\n\n");

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
    +"steps allow for access out of the shaft above, and "
    +"further down into the darkness. The shaft seems to be "
    +"magically supported by roots in order to prevent its "
    +"collapse.\n");

    add_item(({"up", "ceiling", "roof", "exit", "shaft", 
    "vertical shaft", "dark vertical shaft"}),
    "This shaft is vertical, and right above is the "
    +"exit.\n");
        
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
   // add_exit("/d/Faerun/mere/rooms/metrail4", "up");
    add_exit(WARLOCK_ROOMS_DIR + "shaft2", "down", into_shaft);
    
    reset_faerun_room();
}


void
init()
{
    ::init();

    add_action(exit_shaft, "exit");
    add_action(exit_shaft, "leave");
}


void
reset_room()
{
}



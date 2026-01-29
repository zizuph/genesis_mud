/*
 *
 *
 *
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;


void
create_faerun_room()
{
    setuid();
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    
    set_short("You are in a dark and musty tunnel");
    
    set_long("You are in a dark and musty tunnel. There are "
    +"vines hanging down from the ceiling of the tunnel and growing through the cracks "
    +"of it. "
    +"You feel water drip down onto your back causing the smell of must to spread more. "
    +"There's swamp water seeping through the cracks eroding them more, water goes up to your ankle. "
    +"The murky and mud-filled water makes it hard to wade through the tunnel. "
    +"Dim light comes from the east end of the tunnel beckoning you. "
    +"Draconic screeches come from the exit of the tunnel, you feel compelled to investigate.\n");
    
    add_item(({"vine", "vines", "snake", "snakes"}),
    "The ceiling of the tunnel has vines sprouting through every crack. Small snakes wrap around "
    +"them, waiting for dinner to come by. "
    +"They don't seem to mind seem to mind you, however you should avoid annoying them.\n");
    
    add_item(({"swamp water", "water"}),
    "Your feet are ankle deep in the swamp water. "
    +"You are starting to feel uncomfortable as the water starts slowling rising "
    +"to lead to the dark pit.\n");
    
    add_item(({"roof", "ceiling"}),
    "The ceiling of the tunnel is covered in vines growing with no restraints. "
    +"There are lizards crawling around the ceiling eating small insects.\n");
    
    add_item(({"ground", "floor"}),
    "The swamp water is so murky you can see nothing but a few shadows of small animals.\n");
        
    reset_faerun_room();
    
    add_exit(ROOM_DIR + "2", "east");
	add_exit(ROOM_DIR + "4", "north");
    
    //add_npc(NPC_DIR +"quest_assassin", 3);
}


public void
init()
{
    ::init();
}


void
reset_faerun_room()
{
	
}

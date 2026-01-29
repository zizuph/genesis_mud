/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 * Added by Nerull 2018
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;


void
create_mere()
{
    set_short("You are standing in front of a large castle");
    
    set_extraline("The air here is moist and rancid. "
    +"The ground you walk on is flooded with swamp water and muddy. "
    +"As you look around you see longhouses and crude reed huts. "
    +"There is a moat in front of you with a castle across it. "
    +"Large pools of water dot the clearing here and "
    +"tangled bushes and trees cover the area making it hard to see in most directions.\n");
    
    add_item(({"ground"}),
    "The ground is covered with swamp water and mud, your feet sinks deep into it.\n");
    
    add_item(({"longhouses", "huts"}),
    "The longhouses are large and spacious while the huts are small and crowded. "
    +"You see lizardmen and bullywugs going in and out of them. "
    +"The bullywugs obviously got the short end of the stick as they are living in the huts. "
    +"They are hauling materials into the hut seemlingly preparing for something. "
    +"They don't notice you because they are distracted and bickering with each other.\n");
    
    add_item(({"moat"}),
    "The moat is wide and deep, it's uneven but it gets the job done.\n");
    
    add_item(({"castle"}),
    "The old castle towers in front of you, giving off a feeling of danger. "
    +"The castle is large and crippled but it still serves as a protective stronghold, "
    +"especially here deep in the mere. The bridge is down allowing resources to be "
    +"transported in, bullywugs and lizardmen obviously could not achieve this "
    +"organization alone.\n");
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "1", "west");
	add_exit(ROOM_DIR + "3", "south");
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

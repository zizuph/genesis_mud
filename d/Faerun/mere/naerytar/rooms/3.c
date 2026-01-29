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
    
    set_short("You are in the barbican of a castle");
    
    set_long("You are in the barbican of a castle. There are "
    +"puddles of mud that have been tracked into the castle from lizardmen going in and out "
    +"of it. "
    +"The creatures inside are on low alert and some are even sleeping, "
    +"you doubt they would let you go farther in. Planks have been laid from the  "
    +"gateway to the causeway and it creates a boardwalk around 10 feet wide for "
    +"the creatures inside, they must not like walking in the same filth as the bullywugs. "
    +"The mud makes the ground slippery and there are a few crude tables around the area. "
	+"The barbican has no windows and lamps sit along the wall giving off dim light. \n");
    
    add_item(({"creature", "creatures"}),
    "There are many creatures lying around doing nothing and doing very "
    +"laxed patrols. In this room there are lizardmen, giant frogs, and bullywugs. "
    +"They're blocking the passage that goes farther in and don't seem to want you going past.\n");
    
    add_item(({"filth", "mud"}),
    "The area is filthy and muddy because no one cleans. "
    +"There's mud and dirt all over the walls and ground making them slippery "
    +"and you cringe at the filth and smell.\n");
    
    add_item(({"table", "tables"}),
    "The tables are very crude with them just being a barrel with a board tossed onto them. "
    +"The benches at the table are crude as well and just like everything else, has mud on them.\n");
    
    add_item(({"lamp", "lamps"}),
    "The lamps give off little to no light because they have not been cleaned in ages.\n");
        
    reset_faerun_room();
    
    add_exit(ROOM_DIR + "2", "north");
	add_exit(ROOM_DIR + "5", "east");
	
    
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

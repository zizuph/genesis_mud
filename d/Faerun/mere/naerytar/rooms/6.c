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
    
    set_short("You are in the outer ward of a castle.");
    
    set_long("You are in the outer ward of a castle. The ground "
    +"here was once hard-packed earth, however the are in front of the "
    +"barracks has been churned and grinded into mud. There are numerous "
    +"lizardmen and bullywugs present here in the outer ward. The lizardmen "
    +"are hard at work training the giant lizards and the bullywugs are "
    +"ordering the lizardmen around or just doing nothing to help out.\n");
    
    add_item(({"lizards", "giant lizards"}),
    "The lizards are being trained to obey the command of the lizardmen. "
    +"The ones that have been sufficiently trained are being led to the stables "
    +"northeast of this area.\n");
    
    add_item(({"ground", "floor"}),
    "The ground his is extremely muddy thanks to the bullywugs. "
    +"The feet of the bullywugs have churned the ground into mud  "
    +"over time making it better terrain for them to traverse.\n");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "5", "southwest");
	add_exit(ROOM_DIR + "7", "north");
	add_exit(ROOM_DIR + "8", "east");
	add_exit(ROOM_DIR + "9", "south");
	add_exit(ROOM_DIR + "10", "west");
	add_exit(ROOM_DIR + "11", "northwest");
    
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

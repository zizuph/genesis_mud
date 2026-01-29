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
    
    set_short("You are on the causeway of a castle");
    
    set_long("You are on the causeway of a castle. The causeway is long "
    +"and looks to be about 180 feet in length. It cross the moat and leads to "
    +"the outer ward of the castle. It has no roof in case attackers were to group "
    +"in the causeway so that arrows could rain down onto them. There is a defensive bulge "
    +"along the east wall of the causeway.\n");
    
    
    add_item(({"bulge", "defensive bulge"}),
    "Currently this bulge is not manned and you are free to pass by. "
    +"In fact, it's never manned and most just walk along the causeway to pass by.\n");
       
    reset_faerun_room();
    
    add_exit(ROOM_DIR + "3", "west");
	add_exit(ROOM_DIR + "6", "northeast");
	
    
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

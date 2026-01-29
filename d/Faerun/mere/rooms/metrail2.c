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
    set_short("You are somewhere deep in the Mere of Dead Men");
    
    set_extraline("While "
    +"the underbrush is thick and hard to maneuver as you keep "
    +"wading in the stinking swamp water, the trail-like pattern "
    +"keeps going further into the mire. You notice a "
    +"blue patch of fabric resting on a small rock beside some "
    +"sort of a rocky cave entrance here.\n");
    
    add_item(({"patch", "patch of fabric", "blue patch",
    "blue patch of fabric"}),
    "The blue patch of fabric definitely belongs to a "
    +"dress. It seems to have been torn off by force and "
    +"placed on a branch here with purpose.\n");
    
    add_item(({"pattern", "trail-like pattern"}),
    "The pattern seems to have been used by more than one "
    +"individual. It cuts through the various trees and "
    +"underbrush like a green corridor. Maybe someone or "
    +"something is using it to haul goods to some location "
    +"deep into the mire?\n");
    
    add_item(({"small rock", "rock"}),
    "The uneven small rock is the size of what you could easily "
    +"grasp with your hand. It seems to be placed with purpose next "
    +"to the dark cave entrance. On top of it rests a blue patch "
    +"of fabric.\n");
    
    add_item(({"entrance", "cave", "dark cave", "dark entrance"}),
    "The cave seems to be a part of a natural rocky formation in "
    +"this area. The entrance is to the south of here and is "
    +"barely visible from "
    +"the path. \n");
    
    add_item(({"underbrush"}),
    "The underbrush consists of various plants and bushes slightly "
    +"shaped like a directional tunnel or path. It leads either one "
    +"way or the other.\n");
    
    add_item(({"large boulder", "boulder"}),
    "Just like any regular boulder in this area. Covered in "
    +"moss, and too heavy to move. It currently partly the "
    +"cave entrance as if someone recently have moved it "
    +"aside.\n");
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "metrail3", "west");
    add_exit(ROOM_DIR + "mecave", "south",0,0,1);
    add_exit(ROOM_DIR + "metrail1", "northeast");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}

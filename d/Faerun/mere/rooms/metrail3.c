/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 * Modified by Nerull 2018
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
    
    set_extraline("As annoying travelling in these parts of the "
    +"mere is due to the underbrush and wading through the "
    +"stinking swamp water, it seems that the area is growing "
    +"more spacious, particularly in the northwestern direction where "
    +"the trail-like pattern goes. You notice a blue patch of "
    +"fabric hanging from a branch here.\n");
    
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
    
    add_item(({"branch"}),
    "While there are a lot of branches from various trees "
    +"here, one branch in particular seems rather "
    +"interesting. On it, someone has tucked a patch of "
    +"blue fabric on it. Interesting.\n");
    
    add_item(({"underbrush"}),
    "The underbrush consists of various plants and bushes slightly "
    +"shaped like a directional tunnel or path. It leads either one "
    +"way or the other.\n");
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "metrail4", "northwest");
    add_exit(ROOM_DIR + "metrail2", "east");
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

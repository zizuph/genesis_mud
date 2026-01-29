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

#define MAX_NPCS 3
#define MERE_NPC    NPC_DIR + "lizardman" 

static object *npc = allocate(MAX_NPCS);

void
create_mere()
{
    set_short("You are somewhere deep in the Mere of Dead Men");
    
    set_extraline("The underbrush in this swamp is thick and hard "
    +"to maneuver, but you notice a trail-like pattern through the trees "
    +"in the southwestern direction as if somebody has recently "
    +"travelled there. You can't help noticing some blue patch "
    +"of fabric hanging from a fine hairlike thread right before "
    +"your face.\n");
    
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
    
    add_item(({"underbrush"}),
    "The underbrush consists of various plants and bushes slightly "
    +"shaped like a directional tunnel or path. It leads either one "
    +"way or the other.\n");
    
    add_item(({"thread", "fine hairlike thread", "hairlike thread"}),
    "On a closer inspection, the thread containing the blue patch is "
    +"actually made of human hair! It is anchored to a branch above "
    +"your head.\n");
    
    add_item(({"branch"}),
    "The branch with the thread belongs to one of the many trees in this "
    +"area. You find nothing interesting about it except for the "
    +"blue patch of fabric that hangs from it.\n");
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me12", "northeast");
    add_exit(ROOM_DIR + "metrail2", "southwest");
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
    int index, npc_count;

    setuid();
    seteuid(getuid());

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 3;

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            npc[index] = clone_object(MERE_NPC);
            npc[index]->move(TO);
            npc[index]->set_random_move(8);
            npc[index]->set_restrain_path(ROOM_DIR);
 
        }
    }
}

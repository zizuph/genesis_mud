/*
 * Path in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_FOREST;

#define MAX_NPCS        3

string extraline = "The forest thins to the east and northeast.";

void
create_forest()
{
    set_short("The eastern border of" + FOR_NAME);
    set_extraline(forest_descr2(extraline));
    set_add_forest();
    
    add_exit(FOR_DIR + "kr44", "northwest");
    add_exit(FOR_DIR + "kr35", "south");
    add_exit(FOR_DIR + "kr34", "southwest");
    reset_faerun_room();
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

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 1;


    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            setuid(); 
            seteuid(getuid());

            npc[index] = clone_object(NPC_DIR + "revenant");
            npc[index]->set_restrain_path(FOR_DIR);
            npc[index]->set_random_move(3);
            npc[index]->move(TO);
        }
    }      
}

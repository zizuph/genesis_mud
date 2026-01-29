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

static object vamp_sire;
string extraline = "To the north, a deep ravine cuts through the forest.";

void
create_forest()
{
    set_short("Near the northern border of" + FOR_NAME);
    set_extraline(forest_descr3(extraline));

    set_add_forest();
    set_add_ravine();
    
    add_exit(FOR_DIR + "kr49", "northwest");
    add_exit(FOR_DIR + "kr43", "southeast");
    add_exit(FOR_DIR + "kr42", "southwest");
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

    setuid();
    seteuid(getuid());

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 1;

    /*if(!objectp(vamp_sire))
    {
        vamp_sire = clone_object(NPC_DIR + "vamp_sire");
        vamp_sire->set_restrain_path(FOR_DIR);
        vamp_sire->set_random_move(3);
        vamp_sire->move(TO);
    }*/

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

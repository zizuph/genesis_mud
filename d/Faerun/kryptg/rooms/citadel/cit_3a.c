/*
 * Citadel in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CITADEL;

#define MAX_NPCS 3

static object *npc = allocate(MAX_NPCS);

string extraline = "";

void
create_citadel()
{
    INDOORS;
    NO_STEEDS;
    set_short("Northern corner of the Citadel");
    set_extraline("This is the third floor and it is large. It is made " +
        "of stone blocks and is square shaped and deserted. The room " +
        "looks like it was recently visited but now looks deserted.");

    reset_faerun_room();
    set_add_citadel_out();
    
    add_exit(CIT_DIR + "cit_3x", "south");
    add_exit(CIT_DIR + "cit_3b", "southwest");
    add_exit(CIT_DIR + "cit_3d", "southeast");
//    add_exit(CIT_DIR + "cit_3a_al", "north", "@@exit_check");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    int index, npc_count;

    setuid();
    seteuid(getuid());

    npc_count = 3;

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            npc[index] = clone_object(NPC_DIR + "insectman");
            npc[index]->move(TO);
        }
    }
}


int exit_check()
{
    if(present("insectman", TO))
    {
        write("The insectman blocks your way.\n");
        return 1;
    }
    return 0;
}

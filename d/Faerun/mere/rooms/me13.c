/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
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

string extraline = "The ground is dug up by various claw marks.";

void
create_mere()
{

    set_short("Somewhere in the mere");
    set_extraline(mere_descr2(extraline));
    
    add_claws_ground();
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me10", "northeast");
    add_exit(ROOM_DIR + "me09", "northwest");
    add_exit(ROOM_DIR + "me17", "southeast");
    add_exit(ROOM_DIR + "me16", "southwest");
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

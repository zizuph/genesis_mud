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

string extraline = "A group of dead trees are scattered about, and the "
+"presence of thick vegetation makes the area rather dense. You notice a "
+"narrow trail through the vegetation to the southwest.";

//string extraline = "A group of dead trees are scattered across here.";

void
create_mere()
{

    set_short("Deep in the mere");
    set_extraline(mere_descr1(extraline));
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me09", "northeast");
    add_exit(ROOM_DIR + "me08", "northwest");
    add_exit(ROOM_DIR + "me16", "southeast");
    
    add_item(({"trail", "narrow trail", "opening", "small opening"}),
    "Someone has recently pushed through the thick "
    +"vegetation to the southwest, creating a small opening.\n");
    
    // Warlock guildpath
    add_exit(ROOM_DIR + "metrail1", "southwest",0,0,1);

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

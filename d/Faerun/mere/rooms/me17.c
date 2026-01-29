/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 *
 *Added desc for claw marks
 * -- Clyptas, July 2018
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

static object *npc = allocate(MAX_NPCS), shaman;

string extraline = "A tree stands here. It is covered with claw marks.";

void
create_mere()
{

    set_short("Somewhere in the mere");
	
	add_item(({"claw marks","marks",}),
        "You aren't sure what manner of creature put these here but they look " + 
		"fresh and by the depth of the grooves whatever did this was probably " +
		"angry.\n");
		
	add_item(({"tree"}),
        "A tree stands here, covered in claw marks.\n");
		
    set_extraline(mere_descr6(extraline));
    
    add_claws_trees();
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me14", "northeast");
    add_exit(ROOM_DIR + "me13", "northwest");
    add_exit(ROOM_DIR + "me22", "southeast");
    add_exit(ROOM_DIR + "me21", "southwest");
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

   if(!objectp(shaman))
    {
        shaman = clone_object(NPC_DIR + "shaman");
        shaman->move(TO);
    }

    for(index = 0; index < 3; index++)
    {
        if (!objectp(npc[index]))
        {
            npc[index] = clone_object(MERE_NPC);
            npc[index]->move(TO);
        }
    }
}

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
#define MERE_NPC    NPC_DIR + "bullywug" 

#define BEACH_DIR   "/d/Faerun/red_cliffs/rooms/beach/"

static object *npc = allocate(MAX_NPCS);
string extraline = "";

public int
enter_beach()
{
    write("\n\nYou push through the thick vegetation southwards and find yourself "
    +"at a beach.\n\n");

    return 0;
}

void
create_mere()
{

    set_short("Deep in the mere");
    set_extraline(mere_descr2(extraline));
	/*set_extraline(mere_descr2("A patch of hard rocky "
	+"ground merges from the surface of the swamp."));*/
    
    add_std_herbs("mere");
	
	/*add_item(({"ground", "rocky ground", "hard rocky ground", 
	"hard ground"}),
        "Hidden from view, you notice a small hole here "
		+"leading down into some sort of a cave.\n");*/

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me30", "northeast");
	
    //add_exit(BEACH_DIR + "beach001", "south", enter_beach);
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
            npc[index]->command("emote leaps out of a pool.");
        }
    }
}

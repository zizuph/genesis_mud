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

static object *npc = allocate(MAX_NPCS);
string extraline = "A road runs along the border of the mere.";

void
create_mere()
{

    set_short("Near the edge of the mere");
    set_extraline(mere_descr2(extraline));

    add_road();
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(HR_DIR + "srd03", "northeast");
    add_exit(ROOM_DIR + "me01", "northwest");
    add_exit(ROOM_DIR + "me06", "southeast");
    add_exit(ROOM_DIR + "me05", "southwest");



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

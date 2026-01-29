/*
 * Clone handler for Mere of the Dead Men NPCs
 * -- Finwe, July 2006
 */

inherit "/d/Faerun/std/clone_handler";
 
#include "/d/Faerun/defs.h"
#include "defs.h"
 
void
create_clone_handler()
{
    set_default_area(ROOM_DIR);
    add_clone(NPC_DIR + "bullywug", 1, 15);
    add_clone(NPC_DIR + "lizardman",2, 15);
    
    set_clone_handler_id("Mere Clone Handler");
} 

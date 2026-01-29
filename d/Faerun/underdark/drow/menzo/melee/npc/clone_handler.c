/*
 * This handles all npcs in Melee-magthere
 * -- Finwe, April 2006
 */
inherit "/d/Faerun/std/clone_handler";
 
#include "/d/Faerun/defs.h"
#include "defs.h"


void
create_clone_handler()
{
    set_default_area(MELEE_DIR);
// add_clone(filename, id_num, num of npcs to clone);
    add_clone(NPC_DIR + "student", 1, 65);

    set_clone_handler_id("Melee-magthere Clone Handler");
} 

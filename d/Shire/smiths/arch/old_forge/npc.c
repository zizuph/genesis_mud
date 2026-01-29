/*
 * Forge NPC for forge room
 *  
 * This file is an example/template to create a working
 * npc for the forge room.
 *
 * This file is may be customized by changing the respective
 * FORGE_NPC values in forge.h instead of in this file.
 *
 * This npc is called by the forge room
 *
 * -- Finwe, January 2001

 * Finwe, January 2001
 */  

/*
 * Required files and defs
 */
inherit "/d/Shire/smiths/forge/base_forge_npc";
inherit "/sys/global/money";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"
#include <stdproperties.h>
#include <ss_types.h>
// end of required files


/*
 * Domain specific defs
 */

// end of domain files

void
create_monster()
{
    if (!IS_CLONE)
        return;

    add_name(FORGE_NPC_NAME, "smiths_guild_keeper");
    set_living_name(FORGE_NPC_NAME);
    set_race_name(FORGE_NPC_RACE); 
    set_adj(({FORGE_NPC_ADJ1, FORGE_NPC_ADJ2}));
    set_long("This elf is a skilled smith who probably knows the fine art of metal working. \n");
    set_default_answer(QCTNAME(TO)+" tells you: I do not understand you.\n");

}

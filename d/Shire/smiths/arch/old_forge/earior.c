/*
 *  Smiths Guild NPC in Rivendell.
 *  Based on /d/Shire/smiths/npc/berim.c
 * 
 *  Finwe, January 2001
 */  

/*
 * Required files and defs
 */
inherit "/d/Shire/smiths/forge/base_forge_npc";
inherit "/sys/global/money";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

/*
 * Domain specific defs
 */
#include "/d/Shire/sys/defs.h"


void
create_monster()
{
    if (!IS_CLONE)
        return;

    add_name(FORGE_NPC_NAME);
    set_living_name(FORGE_NPC_NAME);
    set_race_name(FORGE_NPC_RACE); 
    set_adj(({FORGE_NPC_ADJ1, FORGE_NPC_ADJ2}));
    set_long("This elf is a skilled smith who probably knows the fine art of metal working. \n");
    set_default_answer(QCTNAME(TO)+" tells you: I do not understand you.\n");

}

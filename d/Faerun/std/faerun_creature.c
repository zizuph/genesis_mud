/*
 *  faerun/std/faerun_creature.c
 *
 *  General file for all the Faerun MONSTERS
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/creature"; /* This to produce a non humanoid monster */ 
inherit "/std/combat/unarmed"; 
inherit "/d/Faerun/std/team_code";

/* Does not seem to work with /std/creature */
// inherit "/d/Faerun/lib/assist_friend";

/*
 * Function name: create_faerun_npc
 * Description  : Contruct our monster
 */
void create_faerun_npc()
{
}

/*
 * Function name: create_monster
 * Description  : Construct our standard humanoid like creature
 */
void create_creature()
{
    // Construct our monster
    create_faerun_npc();
}

/*
 *  Smiths Guild NPC in Rivendell.
 *  Based on /d/Shire/smiths/npc/berim.c
 * 
 *  Finwe, January 2001
 */  

/*
 * Required files and defs
 */
inherit "/d/Shire/smiths/forge/base_forge_mer";
inherit "/sys/global/money";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

/*
 * Domain specific defs
 */
#include "/d/Shire/sys/defs.h"
//string npc_merch_name = "earior";

void
create_merch_npc()
{

set_npc_merch_name("earior");
set_npc_merch_race("goblin");
set_npc_merch_adj1("strong");
set_npc_merch_adj2("stinky");
set_npc_merch_long("This is the stinky merchant for the iron workers in Larstown.\n");

}

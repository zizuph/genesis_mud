/* 
 * /d/Kalad/common/guilds/new_thanar/guildhall/spells/summon_soul.c
 * 
 * Soul for the messenger summon for thanar racial guild.
 */


inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "../guild.h"

string
get_soul_id() 
{ 
    return "thanar summon soul"; 
}

int 
query_cmd_soul() 
{ 
    return 1; 
}

mapping
query_cmdlist()
{
    return ([  ]);
}

public mapping
query_ability_map()
{
    return ([
             "summon" : GSPELLS + "summon.c",
            ]);
}
#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
/*
 * Ckrik - Initial commit 7/7/2020
 *
 */

#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define BASE ("/d/Faerun/guilds/fire_knives")

public string *
query_guild_shadows_fire_knives()
{
    return ({ BASE + "/shadows/fireknives_sh_occ" });
}

public string *
query_guild_souls_fire_knives()
{
    return ({ BASE + "/souls/fireknives_guild_soul" });
}

public mapping
query_guild_skills_fire_knives()
{
    return ([ 
            1527001         : 100,
            SS_SNEAK        : 100,    
            SS_HIDE         : 100,
            SS_WEP_KNIFE    : 100,
            SS_AWARENESS    : 100,
            SS_PARRY        :  75,
            SS_DEFENSE      :  75,
            SS_2H_COMBAT    :  75,
            SS_ALCHEMY      :  40,
            SS_HERBALISM    :  50,
            SS_APPR_MON     :  60,
            SS_CLIMB        :  75,
            SS_BACKSTAB     : 100,
        ]);              
}

public int
start_guild_fire_knives(object player)
{
    return 1;
}

public int
stop_guild_fire_knives(object player)
{
    return 1;
}

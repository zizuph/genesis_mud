/*
 * Calian Warriors module for Guild testing
 * 
 * Created by Petros, March 2009
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public string *
query_guild_shadows_calian()
{
    return ({ "/d/Calia/guilds/calians/specials/calian_shadow" });
}

public string *
query_guild_souls_calian()
{
    return ({ "/d/Calia/guilds/calians/specials/calian_cmdsoul" });
}

public mapping
query_guild_skills_calian()
{
    return ([  
                114001          : 100, // move behind
                114007          : 100, // swarm
                114009          : 100, // riposte    
                SS_WEP_SWORD    : 100,
                SS_DEFENCE      : 75,
                SS_PARRY        : 75,
                SS_UNARM_COMBAT : 30,
                SS_BLIND_COMBAT : 20,
              ]);              
}

public int
start_guild_calian(object player)
{
    return 1;
}

public int
stop_guild_calian(object player)
{
    object * effects, * calian_effects;
    object teamobj;
    
    effects = player->query_evade_effects();
    if (pointerp(effects))
    {
        calian_effects = filter(effects, &->is_swarm_evade()) 
                       + filter(effects, &->is_riposte_evade());
        calian_effects->remove_object();
    }
    
    player->remove_opportunity_attack_shadow();
    if (objectp(teamobj = present("_calian_team_obj", player)))
    {
        teamobj->remove_object();
    }
    
    return 1;
}

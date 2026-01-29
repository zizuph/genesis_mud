/*
 * Vampyrs of Terel module for Guild testing
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
query_guild_shadows_vamp()
{
    return ({ "/d/Terel/guilds/vamp/shadow/occ_shadow" });
}

public string *
query_guild_souls_vamp()
{
    return ({ "/d/Terel/guilds/vamp/soul/occ_soul" });
}

public mapping
query_guild_skills_vamp()
{
    return ([ 
                SS_WEP_SWORD    : 85,
                SS_WEP_AXE      : 85,
                SS_DEFENCE      : 100,
                SS_PARRY        : 75,
                SS_UNARM_COMBAT : 75,
                SS_BLIND_COMBAT : 50,
                130011          : 100, // flurry
                130010          : 100, // bite
              ]);              
}

public int
start_guild_vamp(object player)
{
    return 1;
}

public int
stop_guild_vamp(object player)
{
    object drainobj;
    if (objectp(drainobj = present("_hidden_vamp_drain_object", player)))
    {
        drainobj->remove_object();
    }
    
    return 1;
}

/*
 * Bloodguard module for Guild testing
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
query_guild_shadows_bloodguard()
{
    return ({ "/d/Terel/guilds/vamp/shadow/lay_shadow" });
}

public string *
query_guild_souls_bloodguard()
{
    return ({ "/d/Terel/guilds/vamp/soul/lay_soul" });
}

public mapping
query_guild_skills_bloodguard()
{
    return ([ 
                130010      : 100, // bite
              ]);              
}

public int
start_guild_bloodguard(object player)
{
    return 1;
}

public int
stop_guild_bloodguard(object player)
{
    object drainobj;
    if (objectp(drainobj = present("_hidden_vamp_drain_object", player)))
    {
        drainobj->remove_object();
    }
        
    return 1;
}

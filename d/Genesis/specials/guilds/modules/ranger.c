/*
 * Rangers of the Westland module for Guild testing
 * 
 * Created by Petros, May 2020
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
query_guild_shadows_ranger()
{
    return ({ "/d/Gondor/guilds/rangers/shadow/rangers_shadow_new" });
}

public string *
query_guild_souls_ranger()
{
    return ({ "/d/Gondor/guilds/rangers/soul/rangers_soul_new" });
}

public mapping
query_guild_skills_ranger()
{
    return ([ 
              ]);              
}

public int
start_guild_ranger(object player)
{
    return 1;
}

public int
stop_guild_ranger(object player)
{
    return 1;
}

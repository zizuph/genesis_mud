/*
 * Clans of Khalakhor Racial module for Guild testing
 * 
 * Created by Petros, February 2013
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
query_guild_shadows_clan()
{
    return ({ "/d/Khalakhor/guilds/clans/shadow" });
}

public string *
query_guild_souls_clan()
{
    return ({ "/d/Khalakhor/guilds/clans/soul" });
}

public mapping
query_guild_skills_clan()
{
    return ([ 
              ]);              
}

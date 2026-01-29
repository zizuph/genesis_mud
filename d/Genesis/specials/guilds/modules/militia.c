/*
 * Thornlin Militia module for Guild testing
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
query_guild_shadows_militia()
{
    return ({ "/d/Gondor/guilds/militia/militia_shadow" });
}

public string *
query_guild_souls_militia()
{
    return ({ "/d/Gondor/guilds/militia/militia_soul" });
}

public mapping
query_guild_skills_militia()
{
    return ([ 
                118301      : 50, // militia impale
                118300      : 50, // militia attack
              ]);              
}

public int
start_guild_militia(object player)
{
    return 1;
}

public int
stop_guild_militia(object player)
{
    object boots;
    
    if (objectp(boots = present("_ithilien_badge", player)))
    {
        boots->remove_object();
    }
    
    return 1;
}

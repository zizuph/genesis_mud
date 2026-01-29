/*
 * Necromancer module for Guild testing
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
query_guild_shadows_necromancer()
{
    return ({ "/d/Faerun/guilds/nov/shadows/nov_sh" });
}

public string *
query_guild_souls_necromancer()
{
    return ({ "/d/Faerun/guilds/nov/souls/nov_soul" });
}

public mapping
query_guild_skills_necromancer()
{
    return ([ 
              ]);              
}

public int
start_guild_necromancer(object player)
{
    return 1;
}

public int
stop_guild_necromancer(object player)
{
    return 1;
}

/*
 * Faerun Drow Guild module for Guild testing
 * 
 * Created by Petros, April 2010
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

// Defines

public string *
query_guild_shadows_drow()
{
    return ({ "/d/Faerun/guilds/drow/race/shadow" });
}

public string *
query_guild_souls_drow()
{
    return ({ "/d/Faerun/guilds/drow/race/soul" });
}

public mapping
query_guild_skills_drow()
{
    return ([ 
              ]);              
}

public int
start_guild_drow(object player)
{
    return 1;
}

public int
stop_guild_drow(object player)
{
    return 1;
}

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
query_guild_shadows_halfling()
{
    return ({ "/d/Faerun/guilds/halflings/half_shadow" });
}

public string *
query_guild_souls_halfling()
{
    return ({ "/d/Faerun/guilds/halflings/half_soul" });
}

public mapping
query_guild_skills_halfling()
{
    return ([ ]);              
}

public int
start_guild_halfling(object player)
{
    return 1;
}

public int
stop_guild_halfling(object player)
{
    return 1;
}

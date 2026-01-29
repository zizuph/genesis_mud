/*
 * Warlocks Guild module for Guild testing
 * 
 * Created by Finwe, July 2017
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
query_guild_shadows_warlocks()
{
    return ({ "/d/Faerun/guilds/warlocks/shadows/guild_sh_lay" });
}

public string *
query_guild_souls_warlocks()
{
    return ({ "/d/Faerun/guilds/warlocks/souls/guild_soul",
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_warlocks()
{
    return ([ 
              ]);              
}

public int
start_guild_warlocks(object player)
{
    return 1;
}

public int
stop_guild_warlocks(object player)
{
    return 1;
}

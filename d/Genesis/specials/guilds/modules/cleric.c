/*
 * Elemental Clerics of Calia module for Guild testing
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
#define GUILD_MANAGER       "/d/Calia/guilds/elementalists/lib/guild_manager"

public string *
query_guild_shadows_cleric()
{
    return ({ "/d/Calia/guilds/elementalists/shadows/occ_cleric_shadow",
              "/d/Calia/guilds/elementalists/shadows/lay_worshipper_shadow" });
}

public string *
query_guild_souls_cleric()
{
    return ({ "/d/Calia/guilds/elementalists/souls/lay_worshipper_soul", 
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_cleric()
{
    return ([ 
              ]);              
}

public int
start_guild_cleric(object player)
{
    if (IS_PLAYER_OBJECT(player))
    {
        GUILD_MANAGER->add_cleric(player);
    }
    
    return 1;
}

public int
stop_guild_cleric(object player)
{
    if (IS_PLAYER_OBJECT(player))
    {
        GUILD_MANAGER->remove_cleric(player);
    }
    
    return 1;
}

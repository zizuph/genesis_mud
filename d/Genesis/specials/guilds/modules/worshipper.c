/*
 * Elemental Worshippers of Calia module for Guild testing
 * 
 * Created by Petros, March 2013
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
query_guild_shadows_worshipper()
{
    return ({ "/d/Calia/guilds/elementalists/shadows/lay_worshipper_shadow" });
}

public string *
query_guild_souls_worshipper()
{
    return ({ "/d/Calia/guilds/elementalists/souls/lay_worshipper_soul", 
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_worshipper()
{
    return ([ 
              ]);              
}

public int
start_guild_worshipper(object player)
{
    setuid();
    seteuid(getuid());
    if (IS_PLAYER_OBJECT(player))
    {
        GUILD_MANAGER->add_worshipper(player);
    }
    
    return 1;
}

public int
stop_guild_worshipper_old(object player)
{
    setuid();
    seteuid(getuid());
    if (IS_PLAYER_OBJECT(player))
    {
        GUILD_MANAGER->remove_worshipper(player);
    }
    
    return 1;
}

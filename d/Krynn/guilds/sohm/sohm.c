/*
 * School of High Magic in Krynn
 * 
 * Created by Petros, January 2016
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
#define SOHM_MANAGER "/d/Krynn/guilds/sohm/lib/sohm_manager"

public string *
query_guild_shadows_sohm()
{
    return ({ "/d/Krynn/guilds/sohm/shadows/sohm_shadow" });
}

public string *
query_guild_souls_sohm()
{
    return ({ "/d/Krynn/guilds/sohm/souls/sohm_soul", 
              "/d/Krynn/guilds/sohm/souls/common_spell_soul",
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_sohm()
{
    return ([  SS_DEFENCE :  45, // defence
              ]);           
}

public int
start_guild_sohm(object player)
{

    if (IS_PLAYER_OBJECT(player))
    {
        SOHM_MANAGER->add_member(player);
    }

    return 1;
}

public int
stop_guild_sohm(object player)
{
    object guild_obj;

    if (objectp(guild_obj = present("sohm_guild_object", player)))
    {
        guild_obj->remove_object();
    }
    
    if (IS_PLAYER_OBJECT(player))
    {
        SOHM_MANAGER->remove_member(player);
    }

    return 1;
}

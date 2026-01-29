/*
 * Academy of Elemental Arts module for Guild testing
 * 
 * Created by Petros, September 2009
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
#define ACADEMIC_MANAGER "/d/Calia/guilds/academics/lib/academy_manager"

public string *
query_guild_shadows_academic()
{
    return ({ "/d/Calia/guilds/academics/shadows/academy_shadow" });
}

public string *
query_guild_souls_academic()
{
    return ({ "/d/Calia/guilds/academics/souls/academy_soul", 
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_academic()
{
    return ([  SS_WEP_CLUB : 100, // sword
               SS_PARRY :  80, // parry
               SS_DEFENCE :  90, // defence
              ]);           
}

public int
start_guild_academic(object player)
{
    if (IS_PLAYER_OBJECT(player))
    {
        ACADEMIC_MANAGER->add_member(player);
    }
    return 1;
}

public int
stop_guild_academic(object player)
{
    object guild_obj;
    
    if (objectp(guild_obj = present("academic_guild_object", player)))
    {
        guild_obj->remove_object();
    }
    
    if (IS_PLAYER_OBJECT(player))
    {
        ACADEMIC_MANAGER->remove_member(player);
    }
    
    return 1;
}

/*
 * Example Caster module for Guild testing
 * 
 * Created by Petros, February 2010
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
query_guild_shadows_caster()
{
    return ({ "/d/Genesis/specials/guilds/shadows/example_caster_shadow" });
}

public string *
query_guild_souls_caster()
{
    return ({ "/d/Genesis/specials/guilds/souls/example_caster_soul", 
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_caster()
{
    return ([ 
              ]);              
}

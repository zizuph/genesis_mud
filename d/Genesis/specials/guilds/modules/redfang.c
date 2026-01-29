/*
 * Red Fang Racial module for Guild testing
 * 
 * Created by Petros, August 2012
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
query_guild_shadows_redfang()
{
    return ({ "/d/Kalad/common/guilds/red_fang/obj/fang_shadow" });
}

public string *
query_guild_souls_redfang()
{
    return ({ "/d/Kalad/common/guilds/red_fang/commands/fang_soul" });
}

public mapping
query_guild_skills_redfang()
{
    return ([ 
              ]);              
}

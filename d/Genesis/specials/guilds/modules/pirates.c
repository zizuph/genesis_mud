/*
 * Pirates module for Guild testing
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
query_guild_shadows_pirates()
{
    return ({ "/d/Ansalon/guild/pirates/shadow/pirate_shadow" });
}

public string *
query_guild_souls_pirates()
{
    return ({ "/d/Ansalon/guild/pirates/soul/pirate_soul" });
}

public mapping
query_guild_skills_pirates()
{
    return ([ 
                143030      : 100, // stagger
              ]);              
}

public int
start_guild_pirates(object player)
{
    return 1;
}

public int
stop_guild_pirates(object player)
{
    return 1;
}

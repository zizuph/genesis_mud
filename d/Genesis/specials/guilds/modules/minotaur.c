/*
 * Minotaurs module for Guild testing
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
query_guild_shadows_minotaur()
{
    return ({ "/d/Ansalon/guild/minotaurs/lay_shadow" });
}

public string *
query_guild_souls_minotaur()
{
    return ({ "/d/Ansalon/guild/minotaurs/cmdsoul" });
}

public mapping
query_guild_skills_minotaur()
{
    return ([ 
                143015      : 100, // gore
              ]);              
}

public int
start_guild_minotaur(object player)
{
    return 1;
}

public int
stop_guild_minotaur(object player)
{
    return 1;
}

/*
 * Morgul Mages module for Guild testing - Old Mage
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

public string *
query_guild_shadows_oldmage()
{
    return ({ "/d/Gondor/guilds/morgulmage/morgul_shadow" });
}

public string *
query_guild_souls_oldmage()
{
    return ({ "/d/Gondor/guilds/morgulmage/morgul_soul" });
}

public mapping
query_guild_skills_oldmage()
{
    return ([ 
              SS_WEP_SWORD : 30,
              ]);              
}

public int
start_guild_oldmage(object player)
{
    return 1;
}

public int
stop_guild_oldmage(object player)
{
    return 1;
}

/*
 * Zhar's Blademaster/Clan Guild module for Guild testing
 * 
 * Created by Petros, November 2012
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
query_guild_shadows_zhar_bm_clan()
{
    return ({ 
              "/w/zhar/projects/khalakhor/testing/clan_shadow",
              "/w/zhar/projects/khalakhor/testing/bm_shadow", });
}

public string *
query_guild_souls_zhar_bm_clan()
{
    return ({ "/d/Khalakhor/guilds/blademasters/special/blade_soul" });
}

public mapping
query_guild_skills_zhar_bm_clan()
{
    return ([ 
              ]);              
}

public int
start_guild_zhar_bm_clan(object player)
{
    return 1;
}

public int
stop_guild_zhar_bm_clan(object player)
{
    return 1;
}

/*
 * Cadets of Gelan module for Guild testing
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

public string *
query_guild_shadows_cadet()
{
    return ({ "/d/Calia/gelan/cadet/cadet_shadow" });
}

public string *
query_guild_souls_cadet()
{
    return ({ "/d/Calia/gelan/cadet/cadet_soul" });
}

public mapping
query_guild_skills_cadet()
{
    return ([ 
              ]);              
}

public int
start_guild_cadet(object player)
{
    return 1;
}

public int
stop_guild_cadet(object player)
{
    return 1;
}

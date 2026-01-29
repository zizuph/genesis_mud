/*
 * Gnomish Inventors Guild module for Guild testing
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
query_guild_shadows_inventor()
{
    return ({ "/d/Krynn/gnome/guild/obj/race_shadow" });
}

public string *
query_guild_souls_inventor()
{
    return ({ "/d/Krynn/gnome/guild/obj/kgnome_soul" });
}

public mapping
query_guild_skills_inventor()
{
    return ([ 
              ]);              
}

public int
start_guild_inventor(object player)
{
    return 1;
}

public int
stop_guild_inventor(object player)
{
    return 1;
}

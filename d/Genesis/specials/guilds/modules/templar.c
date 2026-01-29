/*
 * Templar Knights module for Guild testing
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
query_guild_shadows_templar()
{
    return ({ "/d/Krynn/guilds/templar/obj/shadow" });
}

public string *
query_guild_souls_templar()
{
    return ({ "/d/Krynn/guilds/templar/obj/cmdsoul" });
}

public mapping
query_guild_skills_templar()
{
    return ([ 
                108600      : 100, // tattack
                108602      : 100, // sap
                108601      : 100, // tdefend
              ]);              
}

public int
start_guild_templar(object player)
{
    return 1;
}

public int
stop_guild_templar(object player)
{
    object * effects;
    object mantle;
    
    effects = player->query_evade_effects();
    if (pointerp(effects))
    {
        effects = filter(effects, &operator(==)("_templar_evade_object_") 
                         @ &->query_name());
        effects->remove_object();
    }
    
    if (objectp(mantle = present("Templars of Takhisis item", player)))
    {
        mantle->remove_object();
    }
    
    return 1;
}

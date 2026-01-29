/*
 * Army of Angmar (layman) module for Guild testing
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
query_guild_shadows_aa_lay()
{
    return ({ "/d/Shire/guild/AA/shadow/aa_sh_lay" });
}

public string *
query_guild_souls_aa_lay()
{
    return ({ "/d/Shire/guild/AA/soul/aa_soul" });
}

public mapping
query_guild_skills_aa_lay()
{
    return ([ 
                112201          : 100, // shield
                112202          : 100, // smack
                112200          : 100, // smash
              ]);              
}

public int
start_guild_aa_lay(object player)
{
    return 1;
}

public int
stop_guild_aa_lay(object player)
{
    object * effects;
    
    effects = player->query_evade_effects();
    if (!pointerp(effects))
    {
        return 1;
    }
    
    effects = filter(effects, &->query_aa_evade_effect());
    effects->remove_object();

    return 1;
}

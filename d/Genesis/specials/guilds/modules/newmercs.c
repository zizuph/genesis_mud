/*
 * Mercenaries module for Guild testing
 * 
 * Created by Petros, October 2009
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
query_guild_shadows_newmercs()
{
    return ({ "/d/Sparkle/guilds/new_merc/shadows/occ_shadow" });
}

public string *
query_guild_souls_newmercs()
{
    return ({ "/d/Sparkle/guilds/new_merc/souls/cmdsoul" });
}

public mapping
query_guild_skills_newmercs()
{
    return ([  
              SS_WEP_SWORD      : 100,
              SS_DEFENCE        : 100,
              SS_PARRY          : 100,
              151011            : 100, // mercenary tactics (special)
              SS_BLIND_COMBAT   :  75,
              SS_UNARM_COMBAT   :  75,
              SS_2H_COMBAT      : 100,
              ]);              
}

public int
start_guild_newmercs(object player)
{
    return 1;
}

public int
stop_guild_newmercs(object player)
{   
    return 1;
}

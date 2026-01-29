/*
 * Neidar Clan module for Guild testing
 * 
 * Created by Petros, April 2009
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
query_guild_shadows_neidar()
{
    return ({ "/d/Ansalon/guild/neidar/shadows/occ_shadow" });
}

public string *
query_guild_souls_neidar()
{
    return ({ "/d/Ansalon/guild/neidar/souls/cmdsoul" });
}

public mapping
query_guild_skills_neidar()
{
    return ([  
             SS_WEP_AXE :   100,
             SS_DEFENCE :    90,
             SS_PARRY   :    90,
             143002     :   100, // SS_GUILD_SPECIAL_SKILL
              ]);              
}

public int
start_guild_neidar(object player)
{
    return 1;
}

public int
stop_guild_neidar(object player)
{
    object emblem;
    
    if (objectp(emblem = present("Dwarven Warriors of the Neidar Clan emblem", 
                                 player)))
    {
        emblem->remove_object();
    }
    
    return 1;
}

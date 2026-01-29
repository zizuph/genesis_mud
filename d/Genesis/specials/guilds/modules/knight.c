/*
 * Knights of Solamnia module for Guild testing
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
query_guild_shadows_knight()
{
    return ({ "/d/Krynn/guilds/knights/shadows/occ_shadow" });
}

public string *
query_guild_souls_knight()
{
    return ({ "/d/Krynn/guilds/knights/souls/solamnian_soul" });
}

public mapping
query_guild_skills_knight()
{
    return ([  0 : 100, // sword
              26 : 100, // block
             105 :  30, // animal handling
           67530 : 100, // rescue
             112 :  40, // riding
              25 : 100, // mounted combat
              23 :  90, // parry
              24 :  75, // defence
           67531 : 100, // kattack
    SS_2H_COMBAT :  60,
              ]);              
}

public int
start_guild_knight(object player)
{
    return 1;
}

public int
stop_guild_knight(object player)
{
    object medal;
    
    if (objectp(medal = present("pal_med", player)))
    {
        medal->remove_object();
    }
    
    return 1;
}

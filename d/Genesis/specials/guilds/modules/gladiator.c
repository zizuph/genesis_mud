/*
 * Gladiators of Athas module for Guild testing
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
query_guild_shadows_gladiator()
{
    return ({ "/d/Cirath/athas/gladiator/glad_sh" });
}

public string *
query_guild_souls_gladiator()
{
    return ({ "/d/Cirath/athas/gladiator/glad_soul" });
}

public mapping
query_guild_skills_gladiator()
{
    return ([ 
                SS_WEP_AXE      : 100,
                SS_DEFENCE      : 90,
                SS_PARRY        : 90,
                SS_UNARM_COMBAT : 30,
                SS_BLIND_COMBAT : 20,
                142001          : 100, // charge
                142000          : 100, // berserk
              ]);              
}

public int
start_guild_gladiator(object player)
{
    return 1;
}

public int
stop_guild_gladiator(object player)
{
    return 1;
}

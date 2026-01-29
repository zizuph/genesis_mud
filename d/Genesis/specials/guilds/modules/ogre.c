/*
 * Armies of Darkness (ogre) module for Guild testing
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
query_guild_shadows_ogre()
{
    return ({ "/d/Emerald/common/guild/aod/aod_shadow",
              "/d/Emerald/common/guild/aod/race_shadow" });
}

public string *
query_guild_souls_ogre()
{
    return ({ "/d/Emerald/common/guild/aod/cmdsoul" });
}

public mapping
query_guild_skills_ogre()
{
    return ([  SS_WEP_CLUB      :   100,
               SS_DEFENCE       :    75,
               SS_PARRY         :    75,
               SS_2H_COMBAT     :   100,
               SS_UNARM_COMBAT  :    90,
               SS_SWIM          :    50,
               132010           :   100, // crush
              ]);              
}

public int
start_guild_ogre(object player)
{
    player->start_player();
    return 1;
}

public int
stop_guild_ogre(object player)
{
    return 1;
}

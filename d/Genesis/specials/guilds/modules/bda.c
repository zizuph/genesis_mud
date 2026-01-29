/*
 * Blue Dragonarmy module for Guild testing
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
query_guild_shadows_bda()
{
    return ({ "/d/Ansalon/guild/dragonarmy/shadow/dragonarmy_blue_sh" });
}

public string *
query_guild_souls_bda()
{
    return ({ "/d/Ansalon/guild/dragonarmy/soul/dragonarmy_blue_soul" });
}

public mapping
query_guild_skills_bda()
{
    return ([  
                        143008  :   100, // slash
                SS_WEP_SWORD    :   100,    
                SS_BLIND_COMBAT :   75,
                SS_DEFENCE      :   85,
                SS_PARRY        :   85,
                SS_APPR_MON     :   70,
                SS_AWARENESS    :   75,
                SS_ANI_HANDL    :   70,
                SS_2H_COMBAT    :   85,
              ]);              
}

public int
start_guild_bda(object player)
{
    player->set_promotion_level(4, player);
    return 1;
}

public int
stop_guild_bda(object player)
{
    object horn;
    
    if (objectp(horn = present("_dragonarmy_horn", player)))
    {
        horn->remove_object();
    }
        
    return 1;
}

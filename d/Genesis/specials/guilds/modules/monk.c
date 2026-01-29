/*
 * Dragon Order (monks) module for Guild testing
 * 
 * Created by Petros, December 2010
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
query_guild_shadows_monk()
{
    return ({ "/d/Sparkle/guilds/monks/monastery/soul/shadow_occupational" });
}

public string *
query_guild_souls_monk()
{
    return ({ "/d/Sparkle/guilds/monks/monastery/soul/soul" });
}

public mapping
query_guild_skills_monk()
{
    return ([  
                        147002  :   100, // strike
                        147003  :   100, // plexus
                        151006  :    40, // acquired hit
                        151007  :    40, // acquired pen
                SS_UNARM_COMBAT :   100,    
                SS_BLIND_COMBAT :   90,
                SS_DEFENCE      :   100,
                SS_ACROBAT      :   100,
                SS_APPR_MON     :   50,
                SS_AWARENESS    :   70,
                SS_HERBALISM    :   40,
                SS_ELEMENT_AIR  :   5,
                SS_FORM_DIVINATION : 5,
                SS_APPR_OBJ     :   50,
              ]);              
}

public int
start_guild_monk(object player)
{
    player->m_set_acquired_karma(40, 40);
    return 1;
}

public int
stop_guild_monk(object player)
{
    return 1;
}

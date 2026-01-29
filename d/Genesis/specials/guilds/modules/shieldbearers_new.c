/*
 * Shieldbearers module for Guild testing
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
query_guild_shadows_shieldbearers_new()
{
    return ({ "/d/Ansalon/guild/shieldbearers/dwarf_lay_shadow" });
}

public string *
query_guild_souls_shieldbearers_new()
{
    return ({ "/d/Ansalon/guild/shieldbearers/slam_new_test_soul" });
}

public mapping
query_guild_skills_shieldbearers_new()
{
    return ([ 
    	SS_WEP_AXE :   100,
    	SS_DEFENCE :    90,
    	SS_PARRY   :    90,
    	143014     :   100, // slam
    ]);              
}

public int
start_guild_shieldbearers_new(object player)
{
    return 1;
}

public int
stop_guild_shieldbearers_new(object player)
{
    return 1;
}

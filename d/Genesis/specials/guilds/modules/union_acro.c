/*
 * Union of Shadow module for Guild testing
 * 
 * Created by Petros, September 2009
 */

#pragma no_clone
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines

public string *
query_guild_shadows_union_acro()
{
    return ({ "/d/Avenir/union/shadow" });
}

public string *
query_guild_souls_union_acro()
{
    return ({
	"/d/Avenir/union/occ_soul",
	"/d/Avenir/union/special/test_soul",
    });
}

public mapping
query_guild_skills_union_acro()
{
    return ([ ]); // set in setup_union_acro_effect() in npc_setup.h
}

public int
start_guild_union_acro(object player)
{
    return 1;
}

public int
stop_guild_union_acro(object player)
{    
    return 1;
}

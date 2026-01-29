#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../defs.h"

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>
#include <wa_types.h>

string
get_soul_id() 
{
    return GUILD_NAME + " pet_soul"; 
}

int 
query_cmd_soul() 
{
    return 1; 
}

public mapping
query_ability_map()
{
    return ([
                "attack"      : SPECIALS + "pet_attack",
            ]);
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([
            /* Ability name : Ability function */
                "attack"      : "do_ability",
           ]);
}

public int
query_pet_soul()
{
    return 1;
}
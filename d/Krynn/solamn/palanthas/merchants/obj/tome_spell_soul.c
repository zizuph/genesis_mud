/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 * 
 * Tome spell soul. Coded by Arman 2018.
 */

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

string
get_soul_id() 
{ 
    return "tome spell soul"; 
}

int 
query_cmd_soul() 
{ 
    return 1; 
}

mapping
query_cmdlist()
{
    return ([  ]);
}

public mapping
query_ability_map()
{
    return ([
             "arcanossalur"   : "/d/Krynn/guilds/sohm/spells/teleport",
             "ganimshochraos"   : "/d/Krynn/guilds/sohm/spells/chain_lightning"
            ]);
}

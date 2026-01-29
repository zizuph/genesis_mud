/*
 * Updated by Arman, 28 June 2020
 */

#pragma strict_types
#include "/d/Krynn/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "emotes.c"

string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
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
        "wound" : "/d/Krynn/guilds/hobgob/bleed_special",
    ]);

}

mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */

      "wound"  :  "do_ability",

    ]) + emote_cmdlist();
}

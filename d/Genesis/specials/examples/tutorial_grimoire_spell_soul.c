/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 * 
 * Tutorial grimoire spell soul. Coded by Arman 2017.
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
    return "tutorial grimoire spell soul"; 
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
             "illuminatus" : "/d/Genesis/specials/examples/grimoire_light_spell",
             "demonfethos" : "/d/Genesis/specials/examples/grimoire_demonfethos_spell",
             "aquablast"   : "/d/Genesis/specials/examples/grimoire_aquablast_spell"
            ]);
}

/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 * 
 * WoHS Test grimoire spell soul. Coded by Arman 2017.
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
    return "wohs test grimoire spell soul"; 
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
             "zhinpersvek" : "/d/Krynn/guilds/wohs/test/obj/test_invis_spell",
             "ehtahxiekiv" : "/d/Krynn/guilds/wohs/test/obj/test_scry_spell",
             "dotonobsule"   : "/d/Krynn/guilds/wohs/test/obj/test_mirror_spell",
             "tonashkepesk"   : "/d/Krynn/guilds/wohs/test/obj/test_meteor_spell"
            ]);
}

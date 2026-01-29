/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 * 
 * Tutorial grimoire spell soul. Coded by Arman 2017.
 */

#pragma strict_types

#undef  DOMAIN_DIR
#undef  COMMON_DIR
#define DOMAIN_DIR      "/d/Raumdor/development/shanoga/"
#define COMMON_DIR      DOMAIN_DIR + "common/"

#define PATH            COMMON_DIR + "npc/spells/"

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
    return "lich spell soul"; 
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

//removed stun touch and replaced with paralyze in main code
//"stun_touch"     : "/w/shanoga/spells/stun_touch.c",
public mapping
query_ability_map()
{
    return ([
             "frost_ray"      : PATH + "frost_ray.c",
             "ice_storm"      : PATH + "ice_storm.c",
             "plague_swarm"   : PATH + "plague_swarm.c",
             "magic_missile"  : PATH + "magic_missile.c",
             "life_drain"     : PATH + "life_drain.c"
            ]);
}

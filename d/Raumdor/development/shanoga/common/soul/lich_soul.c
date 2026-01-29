#pragma strict_types

#include "defs.h"

#undef PATH
#define PATH "/d/Raumdor/development/shanoga/common/spell/"

inherit "/d/Genesis/specials/abilities";

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

public mapping
query_ability_map()
{
    return ([
             "frost_ray"      : PATH + "frost_ray",
             "ice_storm"      : PATH + "ice_storm",
             "plague_swarm"   : PATH + "plague_swarm",
             "magic_missile"  : PATH + "magic_missile",
             "life_drain"     : PATH + "life_drain"
            ]);
}

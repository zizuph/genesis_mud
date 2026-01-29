#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit DRAGONARMY_BASE_SOUL;

int
query_cmd_soul() 
{
    return 1; 
}

string 
get_soul_id()
{
    return "Green " + GUILD_NAME;
}

public mapping
query_ability_map()
{
    return ([
    "slash"         : DRAGONARMY_SPECIALS + "bda_slash",
     ]) + ::query_ability_map();
}

mapping
query_cmdlist()
{
    return ([
#ifndef NO_DATTACK
        "slash"         : "do_ability",
#endif
    ]) + ::query_cmdlist();
}

void
create()
{
    ::create();
    read_help_dir(DRAGONARMY_HELP + "green/");
}

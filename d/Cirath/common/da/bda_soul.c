#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit DRAGONARMY_BASE_SOUL;

/* mask dattack_message() */
#include "blue_dattack.c"

int
query_cmd_soul() 
{
    return 1; 
}

string 
get_soul_id()
{
    return "Blue " + GUILD_NAME;
}

mapping
query_cmdlist()
{
    return ([
#ifndef NO_DATTACK
      "slash" : "dattack",
#endif
    ]) + ::query_cmdlist();
}

void
create()
{
    ::create();
    read_help_dir(DRAGONARMY_HELP + "blue/");
}

#include "../guild.h"

inherit PROTECTORATE_SOUL_DIR + "warrior_base";

mapping
query_other_cmds()
{
    return ::query_other_cmds() + ([]);
}

void
create_guild_soul()
{
}

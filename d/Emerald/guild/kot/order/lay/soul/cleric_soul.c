#include "../guild.h"

inherit ORDER_SOUL_DIR + "cleric_base";

mapping
query_other_cmds()
{
    return ::query_other_cmds() + ([]);
}

void
create_guild_soul()
{
}

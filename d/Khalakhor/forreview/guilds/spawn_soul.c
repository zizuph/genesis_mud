#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver.c";

#include <std.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <tasks.h>
#include <language.h>
#include "guild.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

string
get_soul_id()
{
    return GUILD_NAME;
}

int
query_cmd_soul()
{
    return 1;
}

string
query_auto_load()
{
    return GUILD_SOUL;
}

mixed
query_alarms()
{
    return get_all_alarms();
}


// Please add new emotes in alphabetical order.
mapping
query_cmdlist()
{
    return ([
    ]);
}

/*
 * Vampires Guild soul racial
 *
 * Nerull, 2021
 *
 */

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include "/d/Faerun/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <login.h>


public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Vampires Racial"; }

public mapping
query_ability_map()
{
    return ([
            ]);
}


public mapping
query_cmdlist()
{
    return ([
            ]);
}

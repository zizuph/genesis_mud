#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <wa_types.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <options.h>


#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h"
inherit SINDAR_RACE_DIR + "sindar_list";
inherit  SINDAR_RACE_DIR + "idea";

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define MORE(x)   this_player()->more(read_file(x,2))


string
get_soul_id()
{
    return "Sindar elves";
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{

    setuid();
    seteuid(getuid());

    return ([
      "help"            : "do_help",

    ]);

}


int
do_help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
    case "sindar":
        MORE(SINDAR_RACE_HELP + "general");
        TP->catch_tell("Please report any problems you may encounter "+
        "with the "+SINDAR_RACE_GUILD_NAME+" to "+
        COMPOSITE_WORDS(map(SINDAR_RACE_GUILD_MASTER, capitalize)) + ".\n");
        break;

    case "sindar general":
        MORE(SINDAR_RACE_HELP + "general");
        break;

    case "sindar emotes":
    case "sindar emotions":
        MORE(SINDAR_RACE_HELP + "emotes");
        break;

    case "sindar news":
        MORE(SINDAR_RACE_HELP + "news");
        break;

    default:
    return 0;
    }
    return 1;
}

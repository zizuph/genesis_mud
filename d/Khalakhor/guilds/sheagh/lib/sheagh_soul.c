#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Khalakhor/guilds/sheagh/lib/help";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include "defs.h"
#include "emotes.c"
//#include "forms.c"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

/*
 * Function name: create
 * Description  : Called when loading to set up some initial
 *                variables.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create()
{
    setuid();
    read_help_dir(DOCS + "help/");
    set_help_type(({"sheagh", "sheagh"}));
}

/*
 * Function name: get_soul_id
 * Description  : Returns the id string for this cmdsoul
 * Arguments    : n/a
 * Returns      : "Sheagh d'Eria"
 */
public string
get_soul_id()
{
    return "Sheagh d'Eria";
}

/*
 * Function name: query_cmd_soul
 * Description  : Identifies this object as a cmdsoul.
 * Arguments    : n/a
 * Returns      : 1
 */
int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

/* Commented out
 *
public int
do_bnews(string str)
{
    setuid(); seteuid(getuid());
    TP->more(read_file(DOCS + "news"));
    (SPECIAL + "guildmaster")->update_news(TP->query_name());
    return 1;
}
 *
 */

/*
 * Function name: query_cmdlist
 * Description  : Returns a mapping of all the commands provided
 *                by this soul.
 * Arguments    : n/a
 * Returns      : As described above.
 */       
public mapping
query_cmdlist()
{
    return ([
        "bnews"   : "do_bnews",
        "soath    : "do_oath",        /* emotes.c */
        ]) +
        help_cmdlist();
}

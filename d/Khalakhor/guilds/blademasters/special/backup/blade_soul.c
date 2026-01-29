#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Khalakhor/guilds/blademasters/special/help";

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
#include "forms.c"

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
    set_help_type(({"blademasters", "blademaster"}));
}

/*
 * Function name: get_soul_id
 * Description  : Returns the id string for this cmdsoul
 * Arguments    : n/a
 * Returns      : "Blademasters"
 */
public string
get_soul_id()
{
    return "Blademasters";
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

/*
 * Function name: do_battack
 * Description  : Allows blademasters to attempt to execute a special
 *                attack.
 * Arguments    : str - Who or what to attack.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_battack(string str)
{
    return TP->do_battack(str);
}

public int
do_bnews(string str)
{
    setuid(); seteuid(getuid());
    TP->more(read_file(DOCS + "news"));
    (SPECIAL + "guildmaster")->update_news(TP->query_name());
    return 1;
}

/*
 * Allow em to toggle the decapitation.
 *
 */
public int
do_bdecapitate(string str)
{
    int val;

    val = TP->query_prop(BLADEMASTER_NO_DECAPITATE);

    if (stringp(str))
    {
        str = lower_case(str);
        if (str == "on")
            val = 0;
        if (str == "off")
            val = 1;
    }

    TP->add_prop(BLADEMASTER_NO_DECAPITATE, val);
    write("Decapitate enemies: " + (val ? "Off" : "On") + "\n");
    return 1;
}


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
        "battack" : "do_battack",     /* shadow */
        "bdecapitate" : "do_bdecapitate", 
        "bflip"   : "do_flip",        /* emotes.c */
        "bform1"  : "do_form1",       /* forms.c */
        "bform2"  : "do_form2",       /* forms.c */
        "bform3"  : "do_form3",       /* forms.c */
        "boath"   : "do_oath",        /* emotes.c */
        "bsalute" : "do_salute",      /* emotes.c */
        "bsmile"  : "do_smile",       /* emotes.c */
        "bbreak"  : "do_break",       /* emotes.c */
        "bwar"    : "do_bwar",        /* emotes.c */
        ]) +
        help_cmdlist();
}

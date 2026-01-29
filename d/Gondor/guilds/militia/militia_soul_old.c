/*
 * /d/Gondor/guilds/militia/militia_soul.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of his code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Command soul for the Militia of Thornlin
 * This soul holds the special abilities of the Militia of Thornlin
 *
 * Other relevant files:
 * Jab special    - /d/Gondor/guilds/militia/jab.c
 * Evade special - /d/Gondor/guilds/militia/evade.c
 * Emotions       - /d/Gondor/guilds/militia/emotes.c
 *
 * Gwyneth and Auberon, March 4, 2001
 *
 * Modification log:
 */
#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/lib/help.c";

#include <cmdparse.h>
#include "militia.h"
#include "wep_find.c"
#include "emotes.c"

#define MOREOBJ     "/obj/more"

public void
create()
{
    set_help_type(({ "militia" }));
    read_help_dir(MHELP);
}

/*
 * Function name : get_soul_id
 * Description   : Give a name for this soul
 * Returns       : string - the soul's id
 */
string
get_soul_id()
{
    return "militia";
}

/*
 * Function name : query_cmd_soul
 * Description   :   identify this as a valid cmdsoul
 * Returns       :       1
 */
int
query_cmd_soul()
{
    return 1;
}

public mapping
query_ability_map()
{
    return ([
    "evade" : "/d/Gondor/guilds/militia/specials/militia_evade",
    "jab" : "/d/Gondor/guilds/militia/specials/jab",
    ]);
}

/*
 * Function name : query_cmdlist
 * Description   : Get the commands available on this soul and
 *                 their corresponding function names.
 * Returns       : mapping - a mapping that maps command names
 *                 to function names.
 */
mapping
query_cmdlist()
{
    return ([ 
        "evade"  : "do_ability",
        "jab"    : "do_ability",
        "msay"   : "msay",
        "maloft" : "maloft",
        "mblink" : "mblink",
        "mchew"  : "mchew",
        "mcrouch": "mcrouch",
        "mglare" : "mglare",
        "mgrasp" : "mgrasp",
        "mgreet" : "mgreet",
        "mlean"  : "mlean",
        "mlick"  : "mlick",
        "mlist"  : "mlist",
        "milist" : "mlist",
        "mrub"   : "mrub",
        "msigh"  : "msigh",
        "mwipe"  : "mwipe",
        ]) + help_cmdlist();
}

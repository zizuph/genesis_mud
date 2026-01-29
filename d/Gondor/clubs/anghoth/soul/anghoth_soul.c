/*
 * Soul for the Anghoth club.
 *
 *   Alto, 01 June 2002
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../anghoth_defs.h"

#include "emotes.c"        // Anghoth club emotes.
#include "memberlist.c"    // Anghoth club list.

public void
create()
{
    /* This sets up the help commands and directory. */
    set_help_type(({ "anghoth", "shields" }));
    read_help_dir(ANGHOTH_HELP);
    FIX_EUID;
}

/*
 * Function name: get_soul_id
 * Description  : Give a name for this soul
 * Returns      : string - the soul's id
 */
public string
get_soul_id()
{
    return "The Anghoth of Morgul";
}

/*
 * Function name: query_cmd_soul
 * Description  : Identify this as a valid cmdsoul
 * Returns      : 1 always
 */
public int
query_cmd_soul()
{
    return 1;
}

/*
 * Function name: query_cmdlist
 * Description  : Get the commands available on this soul and their
 *                corresponding function names.
 * Returns      : mapping - a mapping that maps command names to
 *                function names
 */
public mapping
query_cmdlist()
{
    /* PLEASE keep these in alphabetical order !! */

    return ([ 
              "agbattlesong" : "agbattlesong",
              "agcry"        : "agcry",
              "agexamine"    : "agexamine",
              "agexalt"      : "agexalt",
              "ageye"        : "ageye",
              "agfarewell"   : "agfarewell",
              "agfinger"     : "agfinger",
              "aggrovel"     : "aggrovel",
              "agglare"      : "agglare",
              "aggreet"      : "aggreet",
              "aglist"       : "list_active_anghoth",
              "aglook"       : "aglook",
              "agmove"       : "agmove",
              "agscream"     : "agscream",
              "agslap"       : "agslap",
              "agstruck"     : "agstruck",
              "agsuspicion"  : "agsuspicion",
              "agtap"        : "agtap",
              "agwarn"       : "agwarn",
              "agwarcry"     : "agwarcry",
              "agwarn2"      : "agwarn2",
              "agwonder"     : "agwonder",
            ]) + help_cmdlist();
}

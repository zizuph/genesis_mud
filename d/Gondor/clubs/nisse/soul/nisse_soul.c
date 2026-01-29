/*
 *  /d/Gondor/clubs/nisse/soul/nisse_soul.c
 *
 *  Soul for the Nisse Ohtar club.
 *
 *  Deagol, February 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

#include "emotes.c"
#include "memberlist.c"

void
create()
{
    /* This sets up the help commands and directory. */
    set_help_type(({"nisse"}));
    read_help_dir(NISSE_HELP_DIR);
    FIX_EUID;
}

/*
 *  Function name: get_soul_id
 *  Description  : Give a name for this soul
 *  Returns      : string - the soul's id
 */
string
get_soul_id()
{
    return "Nisse Ohtar";
}

/*
 *  Function name: query_cmd_soul
 *  Description  : Identify this as a valid cmdsoul
 *  Returns      : 1 always
 */
int
query_cmd_soul()
{
    return 1;
}

/*
 *  Function name: query_cmdlist
 *  Description  : Get the commands available on this soul and their
 *                 corresponding function names.
 *  Returns      : mapping - a mapping that maps command names to
 *                 function names
 */
mapping
query_cmdlist()
{
    /* PLEASE keep these in alphabetical order !! */

    return ([
              "nibackhand"    : "nibackhand",
              "nibid"         : "nibid",
              "niclasp1"      : "niclasp1",
              "niclasp2"      : "niclasp2",
              "niclean"       : "niclean",
              "niembrace"     : "niembrace",
              "niflex"        : "niflex",
              "nigaze"        : "nigaze",
              "niglance"      : "niglance",
              "niglare"       : "niglare",
              "nihawk"        : "nihawk",
              "nikiss"        : "nikiss",
              "nilist"        : "list_active_nisse",
              "nineck"        : "nineck",
              "ninod"         : "ninod",
              "nipaint"       : "nipaint",
              "nipeer"        : "nipeer",
              "nirespect"     : "nirespect",
              "nisigh"        : "nisigh",
              "nistep"        : "nistep",
              "nistifle"      : "nistifle",
              "nistomp"       : "nistomp",
              "nisummon"      : "nisummon",
              "nitear"        : "nitear",
              "niwarcry"      : "niwarcry",
              "niward"        : "niward",
            ]) + help_cmdlist();
}

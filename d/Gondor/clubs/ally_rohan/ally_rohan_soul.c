/*
 * /d/Gondor/clubs/ally_rohan/ally_rohan_soul.c 
 *  Modeled after:
 *  The Hunter/Huntresse's Club Soul
 *
 * Raymundo, Summer 2021
 *
 * Modification log:
 */
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

#include "ally_rohan.h"
#include "/d/Gondor/defs.h"
#include <language.h>

/* Prototypes */
//public int tally(string name);


string
query_auto_load()
{
   seteuid(getuid());
   return MASTER_OB(TO);
}

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Allies of Rohan"; }


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
    return ([
                  "arpledge"   : "arpledge",
                  "arhelp"  : "arhelp"
         ]) + help_cmdlist();
}

int
arpledge()
{
    write("You pledge your loyalty to Rohan!\n");
    return 1;
}

int
arhelp()
{
   write("This is a very helpful place to look.\n");
 
    return 1;
}


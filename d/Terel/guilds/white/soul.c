/* File:  /d/Terel/guilds/white/soul.c
 * Creator:       Shinto
 * Date:          
 * Modifications:
 * Purpose:       
 * Related Files: 
 * Comments:
 */

#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/guilds/white/lib/white.h"
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
#include "/d/Terel/guilds/white/lib/emotes.h"
#include "/d/Terel/guilds/white/lib/abilities.h"

#define HELP_DIR   "/d/Terel/guilds/white/help/"

/******************************************************
* Soul identifying and autoloading
*******************************************************/

string
get_soul_id()
{
    return "Order of the White";
}

int
query_cmd_soul()
{
    return 1;
}

/*******************************************************
* The list of verbs and functions. Please add new in alphabetical order.
********************************************************/

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([    
      "wcurse":           "do_curse",
      "wsmile":           "do_smile",
      "wwarm":            "do_warm",
      "alacrity":         "alacrity",
      "help":             "help"
           ]);
}


/********************* help ***************************/
int
help(string str)
{
    string subject, filename;

    if (!str)
     return 0;

    if (sscanf(str, "guild %s", subject) != 1)
     if (sscanf(str, "white %s", subject) != 1)
          return 0;


    filename = HELP_DIR + subject;
    if (file_size(filename) > 0) 
    {
     setuid();
     seteuid(getuid());
     cat(filename);
     return 1;
    }
    notify_fail("No help on that subject I'm afraid.\n");
    return 0;
}

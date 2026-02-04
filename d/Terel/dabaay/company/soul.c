/* File:          /d/Terel/company/soul.c
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
#include "/d/Terel/company/lib/company.h"
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
#include "/d/Terel/company/lib/emotes.h"
#include "/d/Terel/company/lib/abilities.h"

#define HELP_DIR     "/d/Terel/company/help/"

/******************************************************
* Soul identifying and autoloading
*******************************************************/

string
get_soul_id()
{
    return "Company of the Silver Dragon";
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
      "ccurse":    "do_curse",
      "csmile":    "do_smile",
        "alacrity":   "alacrity",
      "help":   "help"
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
     if (sscanf(str, "company %s", subject) != 1)
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

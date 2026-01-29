/*
 *    soul.c  
 *
 * Guild soul for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/cmd/std/command_driver";
#include <cmdparse.h>
#include <composite.h>
#include "../defs.h"
#include "emotes.c"

/*
 * Function name: get_soul_id
 * Description  : Give a name for this soul
 * Returns      : string - the soul's id
 */
public string
get_soul_id()
{
    return "Amazon Racial cmdsoul";
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

      return ([
        "amhelp"    : "amhelp",
        "amscan"    : "amscan",
        "amblaze"   : "amblaze",
        "amconcern" : "amconcern",
        "amlist"    : "amlist",
        "amnod"     : "amnod",
        "amgrin"    : "amgrin",
        "amlisten"  : "amlisten",
        "amhungry"  : "amhungry",
        "ampresent" : "ampresent",
		"ampresent2" :"ampresent2",
             ]);
}

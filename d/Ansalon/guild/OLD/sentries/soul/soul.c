/*
 * File Name        : soul.c
 * By               : Elmore and Boron
 * Inspiration from : Pirates by Elmore
 *                    The Neidar Guild by Arman.
 *                    Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 *
 */

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "../local.h"
#include <macros.h>
#include "/d/Krynn/common/defs.h"

/*
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id()
{
    return GUILD_NAME + " soul";
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
int
query_cmd_soul()
{
    return 1;
}

/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
query_cmdlist()
{
    return ([
            /* Command name : Function name */
              "help"        : "help",
           ]);
}

int
help(string str)
{
    if (str == "sword")
    {
        write("The sword of the Knights of Palanthas can do this:\n" +
        "------------------------------------------------------\n" +
        "------------------------------------------------------\n" +
        "Not much ey? Any ideas for emotes should be mailed "+
        "to Boron.\n");
        return 1;
    }

    return 0;
}

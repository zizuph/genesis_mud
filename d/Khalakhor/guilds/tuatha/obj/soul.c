/* File         : /d/Khalakhor/guilds/tuatha/obj/soul.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 14, 1999
 * Purpose      : This is the command soul of the Tuatha.
 * Related Files: 
 * Comments     :
 * Modifications: TODO : lots
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "../guild.h"

public string
get_soul_id()
{
    return GUILD_NAME;
}

public int
query_cmd_soul()
{
    return 1;
}

/***********************************************************************
* The list of verbs and functions. Please add new in alphabetical order.
***********************************************************************/

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([    
      "help":   "help"
           ]);
}


/********************* help ********************************************/
int
help(string str)
{
    string subject, filename;

    if (!str)
	return 0;

    if (sscanf(str, "guild %s", subject) != 1)
	if (sscanf(str, "tuatha %s", subject) != 1)
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


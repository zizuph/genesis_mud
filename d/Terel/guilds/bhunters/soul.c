/*
 soul for bounty hunters guild
 by Udana 05/06
 */
#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <cmdparse.h>
#include "./emotes.c"
#include "commands.c"


/*
 * Function name : get_soul_id
 * Description   : Give a name for this soul
 * Returns       : string - the soul's id
 */
public string get_soul_id()
{
	return "bounty_hunter";
}

/*
 * Function name : query_cmd_soul
 * Description   :   identify this as a valid cmdsoul
 * Returns       :       1
 */
public int query_cmd_soul()
{
	return 1;
}

/*
 * Function name : query_cmdlist
 * Description   : Get the commands available on this soul and
 *                 their corresponding function names.
 * Returns       : mapping - a mapping that maps command names
 *                 to function names.
 */
public mapping query_cmdlist()
{
	return ([ 
		//"help" : "get_help",
		"set" : "trap_here",
		"list" : "list_sth",
		"bhwarn" : "bhwarn",
		"bhlook" : "bhlook",
		"bhoffer" : "bhoffer",
		"bhcoins" : "bhcoins"
		]);
}


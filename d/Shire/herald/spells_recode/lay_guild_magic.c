/*
*  /d/Shire/herald/spells_recode/lay_guild_spells.c
*
*  Command soul for the Heralds, containing the various spells
*  that are available to the players.
*
*  Nerull, 2016
*/

#pragma strict_types

//#include "../defs.h"
#include "../herald.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";




/*
* Function name: get_soul_id
* Description:   Give a name for this soul
* Returns:       string - the soul's id
*/
public string
get_soul_id()
{
	return "Heralds of the Valar Spells";
}





/*
* Function name: query_cmd_soul
* Description:   identify this as a valid cmdsoul
* Returns:       1
*/
public int
query_cmd_soul()
{
	return 1;
}




public mapping
query_cmdlist()
{
	return ([
		    "healme":"do_ability",
	]);
}


public mapping
query_ability_map()
{
	return ([
		   "healme":HERALD_DIR + "spells_recode/heal_self",
	]);
}

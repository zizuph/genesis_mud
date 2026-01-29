/*
*  /d/Faerun/guilds/black_flame/spells/lay_guild_magic.c
*
*  Command soul for the Black flame, containing the various spells
*  that are available to the players.
*
*  Originally created by Eowul, Oktober 6th, 2009, borrowed
*  and modified by Nerull 2021
*/
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
#include "../guild.h"



/*
* Function name: get_soul_id
* Description:   Give a name for this soul
* Returns:       string - the soul's id
*/
public string
get_soul_id()
{
    return "Black Flame Spells";
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
            "flamepurge" : "do_ability",
            "frenzy" : "do_ability",
            "medicate" : "do_ability",  
            "reconstitute" : "do_ability",
			"polymorph" : "do_ability",  
            "flashbang" : "do_ability",
    ]);
}


public mapping
query_ability_map()
{
    return ([
    
           // BASE SPELLS ------------------------------------------------
           "flamepurge" : BF_GUILD_DIR + "spells/bfflamepurge",
           "frenzy" : BF_GUILD_DIR + "spells/bffrenzy",
           "medicate" : BF_GUILD_DIR + "spells/bfmedicate",
           "reconstitute" : BF_GUILD_DIR + "spells/bfreconstitute",
		   "polymorph" : BF_GUILD_DIR + "spells/bfpolymorph",
           "flashbang" : BF_GUILD_DIR + "spells/bfflashbang",
    ]);
}

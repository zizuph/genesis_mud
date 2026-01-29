/*
 * Command Soul for the Academy of Elemental Arts
 *
 * This is the command soul that every member of the Academy will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Petros, September 2009
 */
#pragma strict_types

#include <macros.h>
#include "../defs.h"

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
    return GUILD_NAME + " Soul"; 
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
	     /* Command name : Function name */
	     
	     "palign"   : "do_ability",
	     "pbless"   : "do_ability",     
             "pblind"   : "do_ability",
	     "pcurse"   : "do_ability",
	     "pdark"    : "do_ability",
	     "pdrain"   : "do_ability",
	     "pinvis"   : "do_ability",
	     "pconvert" : "do_ability",
	     "phammer"  : "do_ability"
    ]);
}

public mapping
query_ability_map()
{
    return ([
	     "palign"   : "/d/Ansalon/guild/new_pot/spells/palign",
	     "pbless"   : "/d/Ansalon/guild/new_pot/spells/pbless",
	     "pblind"   : "/d/Ansalon/guild/new_pot/spells/pblind",
	     "pcurse"   : "/d/Ansalon/guild/new_pot/spells/pcurse",
	     "pdark"    : "/d/Ansalon/guild/new_pot/spells/pdark",
	     "pdrain"   : "/d/Ansalon/guild/new_pot/spells/pdrain",
	     "pinvis"   : "/d/Ansalon/guild/new_pot/spells/pinvis",
	     "pconvert" : "/d/Ansalon/guild/new_pot/spells/pconvert",
	     "phammer"  : "/d/Ansalon/guild/new_pot/spells/phammer"
    ]);
}

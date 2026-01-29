/* 
 *  /d/Kalad/common/guilds/new_thanar/spells/deity_spell_soul.c
 *  The spell soul for the Deity Thanar summoned in Kalad.
 *
 *  Created by Zignur Jan 2018.
 *
 */

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "../local.h"

/* Prototypes */
string              get_soul_id();
int                 query_cmd_soul();
mapping             query_cmdlist();
public              mapping query_ability_map();


/*
 * Function name:        get_soul_id
 * Description  :        returns the description of the soul
 * Returns      :        a string with the description of the soul
 */
string
get_soul_id() 
{ 
    return "The spell soul for deity Thanar in Kalad"; 
} /* get_soul_id */

/*
 * Function name:        query_cmd_soul
 * Description  :        querys the cmd_soul, which in this case always
 *                       is 1 (success)
 * Returns      :        1 success
 */
int 
query_cmd_soul() 
{ 
    return 1; 
} /* query_cmd_soul */

/*
 * Function name:        query_cmdlist
 * Description  :        returns the cmd list
 *                      
 * Returns      :        a mapping with the commands
 */
mapping
query_cmdlist()
{
    return ([  ]);
} /* query_cmdlist */

/*
 * Function name:        query_ability_map
 * Description  :        returns a list with the spells
 *                      
 * Returns      :        a mapping with all the spells
 */
public mapping
query_ability_map()
{
    return ([
         "tdrain"    : SPELLS + "deity_drain",
         "tdamage"   : SPELLS + "deity_damage" ,
         "tblind"    : SPELLS + "deity_blind",
         "tstun"     : SPELLS + "deity_stun"
            ]);
} /* query_ability_map */

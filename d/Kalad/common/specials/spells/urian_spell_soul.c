/* 
 *  The spell soul for Urians mage in Kalad
 *  Created October 2017 by Zignur
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

/* Prototypes */
string              get_soul_id();
int                 query_cmd_soul();
mapping             query_cmdlist();
public              mapping query_ability_map();


/*
 * Function name:        get_soul_id
 * Description  :        returns the description of the soul
 * Returns      :        a string with the descriptiopn of the soul
 */
string
get_soul_id() 
{ 
    return "The spell soul for Urians mage servant"; 
}

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
}

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
}

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
             "fireball"    : "/d/Kalad/common/specials/spells/kalad_fireball",
             "shadowblink" : "/d/Kalad/common/specials/spells/shadowblink",
             "blind"       : "/d/Kalad/common/specials/spells/kalad_blind"           
            ]);
}

/*
 * Custom Damage Modification Messages for barkskin
 *
 * Created by Arman August 2017, modified and used 
 * by Nerull for the Warlocks.
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */
 
#pragma strict_types
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit DAM_MOD_OBJ_BASE;

#include "../../guild.h"

                   
/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    ::create_effect();
    set_name("_barkskin_dam_mod_obj");
    add_name( ({"barkskin dam mod obj" }) );
    set_short("hidden barkskin damage modifer object");    
    set_long("A Warlock damage modifier object. One should not be able to see "+
           "it in their inventory.\n");
    setuid();
    seteuid(getuid());
}


/*
 * Function     : query_dam_mod_strength
 * Description  : Function that will be used to gauge the strength of
 *                the damage modifier based on the situation.  
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the damage modifier percentage
 */

/*
public int
query_dam_mod_strength(object player, object attacker, int attack_id)
{
    return ftoi(itof(query_dam_mod_percentage(player)));
}                            
*/


public void
attack_modified(object player, object attacker, int attack_id)
{
    if (!objectp(attacker) || !objectp(player))
    {
        return;
    }
    
    if (query_dam_mod_absorb())
    {
        // absorbs damage
        player->catch_msg("Your barkskin dampens the attack from " 
        +QTNAME(attacker)+", deflecting the blow.\n");
            
        attacker->catch_msg("A skin of hardened bark protect " 
        + QTNAME(player) + " from your attack, deflecting the blow.\n");
            
        player->tell_watcher("A skin of hardened bark protect " 
        +QTNAME(player) +  " from " + QTPNAME(attacker)+ " attack, "
        +"deflecting the blow.\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}
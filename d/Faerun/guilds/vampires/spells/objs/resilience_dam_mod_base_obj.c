/*
 * Custom Damage Modification Messages for resilience
 *
 * Created by Arman August 2017, modified and used 
 * by Nerull for the Vampires.
 */
 
#include "/d/Genesis/specials/local.h"
inherit DAM_MOD_OBJ_BASE;
 
#pragma strict_types
#include <macros.h>


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
    set_name("_resilience_dam_mod_obj");
    add_name( ({"resilience dam mod obj" }) );
    set_short("hidden resilience damage modifer object");    
    set_long("A Vampire damage modifier object. One should not be able to see "+
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
        player->catch_msg("Your supernatural skin deflecs "
        +"the blow from "+QTNAME(attacker)+".\n");
            
        attacker->catch_msg("The supernatural skin of "
        + QTNAME(player) + " deflects the blow.\n");
            
        player->tell_watcher("The supernatural skin of "
        +QTNAME(player) +  " deflects the blow from " 
        + QTPNAME(attacker)+ " attack.\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}
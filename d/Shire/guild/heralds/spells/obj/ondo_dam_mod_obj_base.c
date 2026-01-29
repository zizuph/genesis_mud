/*
 * Custom Damage Modification Messages for ondo
 *
 * Created by Arman May 2018
 */
 
#pragma strict_types
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include "/d/Genesis/specials/local.h"

inherit DAM_MOD_OBJ_BASE;
                   
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
    set_name("_ondo_dam_mod_obj");
    add_name( ({"ondo dam mod obj" }) );
    set_short("hidden ondo damage modifer object");    
    set_long("Ondo damage modifier object. One should not be able " +
           "to see it in their inventory.\n");
    setuid();
    seteuid(getuid());
}

/*
 * Function     : query_dam_mod_valid
 * Description  : Validation function to see whether this damage modifier 
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 *                dt        - int, damage type 
 * Returns      : 0/1 - invalid/valid
 */
public int
query_dam_mod_valid(object player, object attacker, int attack_id, int dt)
{
    int align = attacker->query_alignment();

    return 1;
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
        player->catch_msg("You feel the blow against you is absorbed " +
            "and redirected into the ground.\n");
        attacker->catch_msg("You ineffectually strike " + QTNAME(player) + 
            ", your blow absorbed as if you had struck the earth " +
            "itself.\n");
        player->tell_watcher(QCTNAME(attacker) + " ineffectually " + 
            "strikes at " + QTNAME(player) + ", " + HIS_HER(attacker) +
            " blow absorbed as if hitting the earth itself.\n", 
            ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}


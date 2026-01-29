/*
 * Custom Damage Modification Messages for demonfethos
 *
 * Created by Arman September 2017
 */
 
#pragma strict_types
#include <macros.h>

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
    set_name("_demonfethos_dam_mod_obj");
    add_name( ({"demonfethos dam mod obj" }) );
    set_short("hidden demonfethos damage modifer object");    
    set_long("An tutorial spell object damage modifier object. One should not be able to see "+
           "it in their inventory.\n");
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
    string demon = attacker->query_race_name();

    // The protection doesn't protect against non-demons
    if(demon != "demon")
      return 0;

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
        player->catch_msg("The intricate web of protective magical energies surrounding you " +
            "blocks the attack from " + QTNAME(attacker)+ ", protecting you from harm.\n");
        attacker->catch_msg("The intricate web of protective magical energies " +
            "protect " + QTNAME(player) + " from your attack, deflecting the blow.\n");
        player->tell_watcher("An intricate web of protective magical energies " +
            "protects " +QTNAME(player) +  " from " + QTPNAME(attacker)+ " attack"+
            ", deflecting the blow.\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}


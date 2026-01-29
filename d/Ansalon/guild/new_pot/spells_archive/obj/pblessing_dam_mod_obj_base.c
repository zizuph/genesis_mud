/*
 * Custom Damage Modification Messages for pbless
 *
 * Created by Arman August 2016
 */
 
#pragma strict_types
#include <macros.h>
inherit "/d/Genesis/specials/std/dam_mod_obj_base";
                   
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
    set_name("_pbless_dam_mod_obj");
    add_name( ({"pbless dam mod obj" }) );
    set_short("hidden pbless damage modifer object");    
    set_long("A PoT damage modifier object. One should not be able to see "+
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
    int align = attacker->query_alignment();

    // The blessing doesn't protect against evil enemies
    if(align < -350)
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
    int gLvl = player->query_priest_level();
    int align = attacker->query_alignment();
    float bless_mod;

    // effectiveness of blessing dependent on guild level
    switch (gLvl)
    {   
    	case 0:   // cleric
          bless_mod = 0.5;
          break;
    	case 1:   // priest
          bless_mod = 0.9;
          break;
        default:  // high priest
          bless_mod = 1.0;
    }

    // Strength of the object is equivalent to its percentage.
    return ftoi(bless_mod * itof(query_dam_mod_percentage(player)));
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
        player->catch_msg("Takhisis favours you with her dark blessings, " +
            "intervening in the attack from " + QTNAME(attacker)
            + " and protecting you from harm.\n");
        attacker->catch_msg("The malevolent blessings of a dark goddess protect " + 
           QTNAME(player) + " from your attack, deflecting the blow.\n");
        player->tell_watcher("The malevolent blessings of a dark goddess protect " +
            QTNAME(player) +  " from " + QTPNAME(attacker)+ " attack"+
            ", deflecting the blow.\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}


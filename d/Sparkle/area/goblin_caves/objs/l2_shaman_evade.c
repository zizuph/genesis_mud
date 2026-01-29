/*
 * levels 2 shaman evade
 * Boreaulam, Jul 2015
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"
#include <ss_types.h>

inherit "/d/Genesis/specials/std/evade_obj_base";

void
create_effect()
{
    set_name("_goblin_shaman_evade_object_");
    add_name( ({"goblin_shaman_evade_object" }) );
    set_short("hidden goblin shaman evade object");    
    set_long("The object that grants evade to a goblin shaman. This "
           + "should not be visible by players.\n");

    setuid();
    seteuid(getuid());
	

    set_evade_stats( SS_WIS );
    set_evade_skills( SS_SPELLCRAFT );
    set_evade_combat_aid(99); // total immune
}                           

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{ 
	return 1;
}

/*
 * Function     : query_evade_strength
 * Description  : Function that will be used to gauge the strength of
 *                the evade based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the evasion percentage
 */
public int
query_evade_strength(object player, object attacker, int attack_id)
{
	return 100;
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    player->catch_msg("player_desc \n");
    attacker->catch_msg("attacker_desc \n");
}
/*
 * Neidar Stubborn Bonus
 * 
 * Neidar gain a combat aid damage absorbtion bonus
 * when over time when fighting an opponent.
 * 
 * The bonus slowly builds over the course of a fight.
 *
 * Louie Nov 2008
 *
 */
 
#pragma strict_types

//inherit DAM_MOD_BASE_OBJ;
inherit "/d/Ansalon/guild/dwarf/new/working/dam_mod_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_neidar_stubborn_object_");
    add_name( ({"neidar_stubborn_obj" }) );
    set_short("Stubborn damage absorb object for Neidar Clan");    
    set_long("The Stubborn object for Neidar Clan members.  You shouldn't "+
        "see this.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(STUBBORN_AID);
}                           

/*
 * Function     : remove_neidar_stubborn_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_neidar_stubborn_object()
{
    remove_object();
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
    //Neidar gain the bonus over time.
    //We track the start time of a fight, and update the time
    //on a regular basis.
    //The update time minus the start time will be used to
    //determine how long this particular fight has gone on.

    string name = player->query_name();
    string start_prop = "_"+name+STUBBORN_START_TIME,
        update_prop = "_"+name+STUBBORN_UPDATE_TIME;

    int start_time = attacker->query_prop(start_prop),
        update_time = attacker->query_prop(update_prop)
        cur_time = time();

    //No props, not valid (hasn't fought yet)
    //Also not valid if the times match (no time has elapsed yet)
    if (!start_time || !update_time) {
        attacker->add_prop(start_prop, cur_time);
        attacker->add_prop(update_prop, cur_time);
        return 0;
    }

    //Fight over, not valid (fought, but too long ago to get bonus,
    //so reset)
    if (update_time+STUBBORN_FIGHT_TIME < cur_time) {
        attacker->add_prop(start_prop, cur_time);
        attacker->add_prop(update_prop, cur_time);
        return 0;
    }

    //No time has elapsed yet
    if (start_time == update_time) {
        return 0;
    }

    //Valid, so reset update timer
    attacker->add_prop(update_prop, cur_time);
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
public int
query_dam_mod_strength(object player, object attacker, int attack_id)
{
    int strength;

    max_strength = ::query_dam_mod_strength(player, attacker, attack_id);

    //We scale the absorbtion rate based on the time that 
    //has elapsed to 'build up' the resistance.
    //We scale the actual absorbtion, not the combat aid.
    string name = player->query_name();
    string start_prop = "_"+name+STUBBORN_START_TIME,
        update_prop = "_"+name+STUBBORN_UPDATE_TIME;

    int start_time = attacker->query_prop(start_prop),
        update_time = attacker->query_prop(update_prop)
        cur_time = time();

    //Safety checks
    if (!start_time || !update_time || start_time == update_time ||
        update_time < start_time ) {
        return strength;
    }

    int full_time = STUBBORN_FULL_STRENGTH_TIME;

    int scaled_strength = max_strength * ((update_time - start_time) / full_time);

    send_debug_message("neidar_stubborn", "Neidar stubborn (absorb) max "+
        "strength: "+max_strength+", scaled strength: "+scaled_strength);

    return MIN(max_strength, scaled_strength);

}         
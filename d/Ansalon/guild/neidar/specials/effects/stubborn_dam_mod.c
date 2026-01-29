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

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../guild.h"
#include "/d/Genesis/specials/new/defs.h"

inherit DAM_MOD_OBJ_BASE;

// Defines
#define TICK_INTERVAL       5.0

// Global Variables
public int      combat_ticks = 0;

/*
 * Function:    is_neidar_stubborn_object
 * Description: Indicates whether this is the Neidar Tireless
 *              Object. Used in filters during remove_object
 */
public int
is_neidar_stubborn_object()
{
    return 1;
}

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
    set_short("hidden stubborn damage absorb object");    
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

public void
update_combat_ticks(object player)
{
    if (player->query_combat_time() + ftoi(TICK_INTERVAL) > time())
    {
        // there was combat in the last five seconds
        combat_ticks = min(100, combat_ticks + ftoi(TICK_INTERVAL));
    }
    else
    {
        // no combat, we reduce the combat ticks
        combat_ticks = max(0, combat_ticks - ftoi(TICK_INTERVAL));
    }
}

public int
start()
{
    int result = ::start();
    
    set_alarm(0.0, TICK_INTERVAL, 
        &update_combat_ticks(query_effect_target()));
        
    return result;
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
    if (combat_ticks == 0)
    {
        // If ticks are 0, that means we haven't been in a fight.
        return 0;
    }
    
    return 1;
}

/*
 * Function     : query_dam_mod_combat_aid
 * Description  : returns the damage modifier combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_dam_mod_combat_aid(object player)
{
    int max_aid, scaled_aid;
    
    max_aid = ::query_effect_combat_aid(player);
    // We scale by the combat ticks. Once a Neidar has been in battle for
    // 100 seconds, they will achieve maximum combat aid.
    scaled_aid = max_aid * combat_ticks / 100;
    
    send_debug_message("neidar_stubborn", "Neidar stubborn (absorb) max "+
        "aid: "+max_aid+", scaled aid: "+scaled_aid);

    return min(max_aid, scaled_aid);
}

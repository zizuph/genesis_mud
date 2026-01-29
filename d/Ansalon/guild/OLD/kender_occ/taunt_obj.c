#pragma strict_type

inherit "/d/Genesis/specials/std/dam_mod_obj_base";

#include "guild.h"
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

mixed   rage_alarm;

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name("kender_taunt");
    add_name( ({"kender_taunt_object" }) );
    set_short("hidden kender magic taunt object");    
    set_long("This is the secret and extremely hidden kender taunt object.\n");
    
    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(25);
    set_dam_mod_absorb(0);
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
    object kender, *team, *kenders = ({});
    
    if (player->query_kender_rage() < 1)
        return 0;

    if (objectp(attacker->query_leader()))
        team = attacker->query_leader()->query_team() +
               ({ attacker->query_leader() });
    else
        team = attacker->query_team() + ({ attacker });
    
    team = filter(team, &operator(==)(, environment(player)) @ &environment());
    
    if (!sizeof(team))
        return 0;
    
    foreach(string member: m_indexes(player->query_kender_list()))
    {
        // Check for kenders that only sling + taunt
        if (!objectp(kender = find_player(member)) ||
            player->query_special_attacks(kender) < 0  ||
            environment(kender) != environment(player))
            continue;
        
        kenders += ({ kender });
    }
    
    if (sizeof(kenders) && random((sizeof(team) * 10) / sizeof(kenders)) < 10)
	    return 1;
    
	return 0;
}


/*
 * Function name :  taunt_interval
 * Description   :  Decreases the value of the rage in the shadow, and
 *                  removes this object if the rage is 0.
 */
int
taunt_interval()
{
    object enemy = query_effect_target();
    
    if (enemy->subtract_kender_rage(1) < 0)
        remove_object();
}

/*
 * Function name :  init_rage_decay
 * Description   :  This function sets an alarm to decrease the rage value by
 *                  1 every 2 seconds.
 */
void
init_rage_decay()
{
    if (rage_alarm)
        return;
    
    rage_alarm = set_alarm(2.0, 2.0, &taunt_interval());
}

/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    int     result = ::start();
    object  shadow, enemy;
    
    if (objectp(enemy = environment(this_object())) && living(enemy) &&
        !enemy->query_kender_rage())
    {
        shadow = clone_object(TAUNT_SH);
        shadow->shadow_me(enemy);
        init_rage_decay();
    }
    
    return result;
}

public void
remove_object()
{
    object enemy;
    
    if (objectp(enemy = environment(this_object())) && living(enemy) &&
        !enemy->query_kender_rage())
    {
        enemy->remove_kender_rage();
    }
    
    ::remove_object();
}
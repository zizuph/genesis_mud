/*
 * Interrupt Shadow
 *
 * This is a default shadow that allows interrupt objects to be added to it in 
 * order to support multiple stacking effects, it also handles the actual 
 * prevention of executing abilities.
 * 
 * Created by Carnak, Januari 2018
 */
 
#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"

inherit EFFECT_BASE_SH;

#include "../debugger/debugger_tell.h"

/* Global Variables */
private int     cooldown_alarm;

/*
 * Function name:   has_interrupt_shadow
 * Description:     Verify if the target has been shadowed
 * Arguments:       None
 * Returns:         (int) 1
 */
public int
has_interrupt_shadow()
{
    return 1;
} /* has_interrupt_shadow */

/*
 * Function name:   remove_interrupt_shadow
 * Description:     Remove the interrupt shadow
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_interrupt_shadow()
{
    remove_shadow();
} /* remove_interrupt_shadow */

/*
 * Function name:   query_interrupt_effects
 * Description:     Returns the full list of effects currently being kept
 *                  track of by the interrupt shadow
 * Arguments:       None
 * Returns:         (object *) - array of interrupt effect objects
 */
public object *
query_interrupt_effects()
{
    return query_effects();
} /* query_interrupt_effects */

/*
 * Function name:   remove_interrupt_effect
 * Description:     Removes the effect from the list of effects
 * Arguments:       (object) obj - object to remove
 * Returns:         Nothing
 */
public nomask void
remove_interrupt_effect(object obj)
{
    remove_effect(obj);
} /* remove_interrupt_effect */

/*
 * Function name:   calculate_interrupt_cooldown
 * Description:     Calculate the cooldown of the interrupted ability.
 * Arguments:       (object) obj - effect object
 * Returns:         (int) - interrupted ability cooldown
 */
public int
calculate_interrupt_cooldown(object obj)
{
    object  player, ability = obj->query_interrupted_ability();
    int     value, ability_caid,
            interrupt_time = obj->query_interrupt_cooldown(),
            interrupt_caid = obj->query_interrupt_combat_aid();
    
    player = this_player();
    set_this_player(obj->query_effect_target());
    
    if (ability->query_spell())
        ability_caid = ftoi(ability->query_spell_combat_aid());
    else
        ability_caid = ability->query_combat_aid();
    
    value = (((interrupt_caid * 100) / ability_caid) * interrupt_time) / 100;
    
    set_this_player(player);
    
    return value;
} /* calculate_interrupt_cooldown */

/*
 * Function name:   add_interrupt_effect
 * Description:     Adds the interrupt effect to the list of effects
 * Arguments:       (object) obj - effect to add
 * Returns:         (int) 0 - Interrupt failed.
 *                        1 - Ability interrupted.
 */
public int
add_interrupt_effect(object obj)
{
    object  ability = obj->query_interrupted_ability(),
            caster = obj->query_effect_caster();
    int     cooldown,
            i_time = obj->query_interrupt_cooldown(),
            caid = obj->query_interrupt_combat_aid();
    
    if (member_array(ability, query_interrupt_effects()) > -1)
    {
        obj->hook_ability_already_disabled();
        return 0;
    }
    
    if (!ability->stop_ability(shadow_who))
    {
        /* To make the ability more useful, we can block special_attack on
         * NPCs.
         */
        if (!shadow_who->query_npc())
        {
            obj->hook_ability_unavailable();
            return 0;
        }
        
        cooldown =  (((100 * caid) / (100 + caid)) *
                    ((caster->query_average_stat() * i_time) /
                    shadow_who->query_average_stat())) / 100;
    }
    
    add_effect(obj);
    
    if (!cooldown)
        cooldown = calculate_interrupt_cooldown(obj);
    
    obj->set_dispel_time(cooldown);
    obj->hook_ability_disabled();
    
    return 1;
} /* add_interrupt_effect */

/*
 * Function name:   query_ability_interrupted
 * Description:     This function handles the execute prevention of abilities in
 *                  the interrupt ability.
 * Arguments:       (object) ability - Ability to verify interruption
 * Returns:         (int) 0 - Allow ability
 *                        1 - Interrupt ability           
 */
public int
query_ability_interrupted(object ability)
{
    object *objs;
    
    objs = filter(query_interrupt_effects(), &operator(==)(,ability) @
           &->query_interrupted_ability());
    
    if (sizeof(objs))
    {
        objs[0]->hook_ability_locked();
        return 1;
    }
    
    return 0;
} /* query_ability_interrupted */

/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
public int
special_attack(object victim)
{
    object *objs;
    
    objs = filter(query_interrupt_effects(), &operator(==)(, "special attack") @
           &->query_ability_name());
    
    if (!sizeof(objs))
        return shadow_who->special_attack(victim);
    
    return 0;
} /* special_attack */

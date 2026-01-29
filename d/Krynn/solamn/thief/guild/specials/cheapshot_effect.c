inherit "/d/Genesis/specials/std/interrupt_obj_base.c";

#include <macros.h>

/*
 * Function name:   hook_ability_locked
 * Description;     This is called when an ability is locked.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_locked()
{
    query_effect_target()->catch_msg("You have yet to recover from the cheap "
    + "shot delivered by " + QTNAME(query_effect_caster()) + " which "
    + "interrupted your " + m_interruptAbility->query_ability_name() + ".\n");
} /* hook_ability_locked */

/*
 * Function name:   hook_ability_unavailable
 * Description;     There are no abilities available for interruption.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_unavailable()
{
    query_effect_caster()->catch_msg(QCTNAME(query_effect_target()) + " is "
    + "not preparing any abilities worth interrupting.\n");
} /* hook_ability_unavailable */

/*
 * Function name:   hook_ability_already_disabled
 * Description;     The target ability is already disabled.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_already_disabled()
{
    query_effect_caster()->catch_msg("The "
    + m_interruptAbility->query_ability_name()
    + " has already been disabled.\n");
} /* hook_ability_already_disabled */

/*
 * Function name:   hook_ability_enabled
 * Description;     This is called once the ability is enabled again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_enabled()
{
    object ability, player, target, caster;
    
    player = this_player();
    set_this_player(query_effect_target());
    
    ability = query_interrupted_ability();
    ability->hook_special_complete();
    set_this_player(player);
    
    target = query_effect_target();
    caster = query_effect_caster();
    
    if (!objectp(target) || !objectp(caster))
        return;
    
    tell_room(environment(target), QCTNAME(target) + " seems to have recovered "
    + "from the underhanded attack delivered by " + QTNAME(caster) + ".\n",
    ({ caster, target }), target);
    
    if (environment(caster) == environment(target))
    {
        caster->catch_msg(QCTNAME(target) + " has recovered from your cheap "
        + "shot.\n");
    }
} /* hook_ability_enabled */

/*
 * Function name:   hook_ability_disabled
 * Description;     This is called when the interrupt successfully disabled the
 *                  ability.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_disabled()
{
} /* hook_ability_disabled */

/*
 * Function name:   hook_ability_failed
 * Description;     This is called when this fails to interrupt an ability.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_failed()
{
    query_effect_caster()->catch_msg("You failed to seize the opportunity to "
    + "interrupt " + QTNAME(query_effect_target()) + " from executing "
    + LANG_ADDART(m_interruptAbility->query_ability_name()) + ".\n");
    
    query_effect_target()->catch_msg(QCTNAME(query_effect_caster())
    + " attempted to interrupt your " + m_interruptAbility->query_ability_name()
    + ", but failed.\n");
} /* hook_ability_failed */
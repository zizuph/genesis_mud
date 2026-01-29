/* 
 * /d/Kalad/common/guilds/new_thanar/guildhall/spells/summon_obj.c
 * 
 * Spell file object for the messenger summon for thanar racial guild.
 */


inherit "/d/Genesis/specials/std/spells/obj/summon_obj.c";

#include <macros.h>

/*
 * Function:    customize_summoned_creature
 * Description: Called after the creature has been cloned and summoned, this
 *              allows inheriting spells to customize the summoned creature.
 */
public void
customize_summoned_object(object summon_object, mapping input)
{
} /* customize_summoned_object */

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();
    caster->catch_tell("You stand quietly feeling the surging power of "+
    "Thanar course through you.\nYour summons are heard as a small black "
    +"snake arrives coiling itself along your arm.\n");
    tell_room(environment(caster), QCTNAME(caster) + " stands quietly "
    +"concentrating.\n You feel an eerie dark presence then notice a small "
    +"black snake out of nowhere.\n", ({ caster }), caster);
} /* hook_spell_effect_started */


/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object caster = query_effect_caster();
    if (!objectp(caster))
    {
        return;
    }
    
    if (!objectp(summon_object))
    {
        caster->catch_tell("You sense that your magically summoned "
            + "snake has faded from existence.\n");
        return;
    }
    
    caster->catch_tell("Your sense the magically summoned " 
        + summon_object->short() + " fade from existence.\n");
    tell_room(environment(summon_object), QCTNAME(summon_object)
        + " disappears.\n", ({ caster }));
} /* hook_spell_effect_ended */


/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object caster = query_effect_caster();
    if (!objectp(caster) || !objectp(summon_object))
    {
        return;
    }
    
    caster->catch_tell("Your sense the magically summoned " 
        + summon_object->short() + " begin to fade from existence.\n");    
} /* hook_spell_effect_warn_fading */


/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster) && objectp(summon_object))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the summoned " + summon_object->short() + ".\n");
    }    
} /* hook_spell_effect_not_maintained */
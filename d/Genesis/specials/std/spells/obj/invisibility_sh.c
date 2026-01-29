/*
 *  Support shadow for the standard invisibility spell. Monitors attacks
 *  on and by the player and removes the invisibility effect.
 *
 *  Created by Eowul, July 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

// Global Variables
public object   spell_effect = 0;
public int      invis_in_effect = 0;
public int      power = 0;

// Prototypes
public void     hook_spell_no_fighting(object spell_object, object target);
public void     hook_spell_action_caught(object spell_object, object target);

/*
 * Function     : has_invisibility_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int 
has_invisibility_shadow() 
{
    return has_spell_shadow();
}

/*
 * Function     : remove_invisibility_shadow
 * Description  : Easy way to remove invisibility shadow. 
 * Arguments    : none
 * Returns      : nothing
*/
public void 
remove_invisibility_shadow()
{
    remove_spell_shadow();
}

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_effect = spell_object;
    
    spell_object->set_spell_effect_desc("invisibility");
    spell_object->set_short("invisibility spell object");
    
    power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
    if (invis_in_effect && prop == OBJ_I_INVIS && intp(result))
    {
        result = result + 1;
    }
    
    return result;
}

/*
 * Function:    notify_combat_entered
 * Description: Called by the invisibility shadow when combat is initiated.
 * Arguments:   target - person attacking / being attacked
 */
void notify_combat_entered(object target)
{
    hook_spell_no_fighting(spell_effect, target);
    spell_effect->dispel_effect(target);
}

public void
attack_object(object ob)
{
    shadow_who->attack_object( ob );
    if (objectp(spell_effect))
    {
        notify_combat_entered(ob);
    }  
}

public void
attacked_by(object ob)
{
    shadow_who->attacked_by( ob );
    if (objectp(spell_effect))
    {
        notify_combat_entered(ob);    
    }
}

public void
hook_i_caught_stealing(int success, object item, object from)
{
    shadow_who->hook_i_caught_stealing(success, item, from);

    if (random(100) > (power / 2)) 
    {
        hook_spell_action_caught(spell_effect, from);
        spell_effect->dispel_effect(from);
    }
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You slowly fade from sight.\n");
        tell_room(environment(target), QCTNAME(target) + " slowly fades "
            + "from sight.\n", ({ target }));
    }
    
    invis_in_effect = 1;
    // Need to call the property change functions
    int oldvalue = shadow_who->query_prop(OBJ_I_INVIS);
    int newvalue = oldvalue + 1;
    call_other(shadow_who, "add_prop_obj_i_invis", newvalue); 
    if (environment())
    {
        environment()->notify_change_prop(OBJ_I_INVIS, newvalue, oldvalue);
        environment()->hook_change_invis(shadow_who);
    }
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    invis_in_effect = 0;
    
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You fade back into sight.\n");
        tell_room(environment(target), QCTNAME(target) + " fades "
            + "back into sight.\n", ({ target }));
    }
    // Need to call the property change functions
    int newvalue = shadow_who->query_prop(OBJ_I_INVIS);
    int oldvalue = newvalue + 1;
    if (newvalue <= 0)
    {
        call_other(shadow_who, "remove_prop_obj_i_invis");
    }
    if (environment())
    {
        environment()->notify_change_prop(OBJ_I_INVIS, newvalue, oldvalue);
        environment()->hook_change_invis(shadow_who);
    }    
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel you will soon be visibile again.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "your invisibility.\n");
    }    
}

/*
 * Function:    hook_spell_no_fighting
 * Description: Override this to describe the effect when the caster 
 *              engages someone into battle.
 * Arguments:   target - our enemy that caused us to dispel the effect
 */
public void
hook_spell_no_fighting(object spell_object, object target)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You cannot fight while being invisible.\n");
    }    
}

/* 
 * Function:    hook_spell_action_caught
 * Description: Override this to describe the what happens when the effect
 *              ends because we were caught performing a complex action 
 *              (like stealing)
 */
public void
hook_spell_action_caught(object spell_object, object target)
{
    object caster = spell_object->query_effect_caster();

    if (objectp(caster))
    {
        caster->catch_tell("You fail to stay invisible.\n");
    }
}


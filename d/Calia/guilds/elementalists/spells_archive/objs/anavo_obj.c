/*
 * Ignite Mana Object - based on the Standard Blind Object
 *
 * It tracks that a target has been mana poisoned for a
 * limited duration.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, February 2017.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <poison_types.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_ignite_mana_object_");
    set_short("ignite mana spell object");    
    set_long("This is the standard ignite mana spell object. " +
             "It gives a mana poison to the target.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the ignite mana spell.\n");
    set_spell_effect_desc("ignite mana");
        
    set_dispel_time(600);  
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    return 1;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    object mana_poison = clone_object("/std/poison_effect");
    mana_poison->move(target);
    mana_poison->set_time(600);
    mana_poison->set_interval(20);
    mana_poison->set_strength(100);
    mana_poison->set_damage(({POISON_MANA, 150}));
    mana_poison->set_silent(1);
    mana_poison->start_poison(caster);       
       
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your mind.\n");        
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been mana ignited!\n");
    }
        
    this_object()->start_poison(caster);
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();

    if (objectp(target))
    {
        target->catch_tell("The pain in your mind subsides.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " is no longer "+
            "mana ignited.\n");
    }           
}

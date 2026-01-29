/*
 * Turn Target Object - based on the Standard Blind Object
 *
 * This object gives the target a shadow that makes them
 * run away at the sight of the caster.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, March 2017.
 */

#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

#define FEAR_SHADOW               SPELL_OBJ_DIR + "turn_target_shadow"
#define FEARED_SHADOW             SPELL_OBJ_DIR + "turn_target_caster_shadow"
#define I_HAVE_BEEN_TARGET_TURNED "_i_have_been_target_turned"

void 
create_spell_object()
{
    set_name("_turn_target_ob_");
    set_short("turn target spell object");    
    set_long("This is the standard turn targetspell object. " +
             "It makes the target run away from the caster.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO,"This is the standard spell object "+
        "for the turn target spell.\n");
    set_spell_effect_desc("turn target");
    
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
        
    set_dispel_time(get_default_spell_time()); 

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
    
    int stat;
    object shadow;
    
    setuid();
    seteuid(getuid());
    
    shadow = clone_object(FEAR_SHADOW);
    shadow->set_turn_target_ob(this_object());
    shadow->shadow_me(target);
    shadow = clone_object(FEARED_SHADOW);
    shadow->shadow_me(caster);
    
    caster->set_fear_target(target);
    target->fear_run_away(caster);
    
    target->add_prop(I_HAVE_BEEN_TARGET_TURNED, time());    
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

    if (objectp(caster))
    {
        target->catch_tell("Your fear of " + caster->query_the_name(target) +
            " subsides.\n");
        
        caster->catch_tell("You sense that " + target->query_the_name(caster) +
            " is no longer turned.\n");
    
        setuid();
        seteuid(getuid());
            
        target->remove_turn_target_shadow();
        caster->remove_turn_target_caster_shadow();
    } 
}

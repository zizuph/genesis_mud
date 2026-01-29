/*
 * Turn Undead Object - based on the Standard Blind Object
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

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

#define FEAR_SHADOW "/d/Calia/guilds/elementalists/spells/objs/fear_shadow"
#define FEARED_SHADOW "/d/Calia/guilds/elementalists/spells/objs/feared_shadow"
#define I_HAVE_BEEN_VEKPOSSED "_ec_i_have_been_vekpossed"

void 
create_spell_object()
{
    set_name("_ec_undead_turned_ob_");
    set_short("turn undead spell object");    
    set_long("This is the standard turn undead spell object. " +
             "It makes the target run away from the caster.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO,"This is the spell object for the Vekpos "+
        "spell of the Elemental Clerics guild. It is a turn" +
        " undead spell, and this object sets up a shadow in both the" +
        " target and caster, so the the target flees at the sight of" +
        " the caster for the duration.\n");
    set_spell_effect_desc("turn undead");
    
    set_dispel_time(200+random(60)); 
    
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
    
    int stat;
    object shadow;
    
    setuid();
    seteuid(getuid());
    
    shadow = clone_object(FEAR_SHADOW);
    shadow->set_vekpos_ob(this_object());
    shadow->shadow_me(target);
    shadow = clone_object(FEARED_SHADOW);
    shadow->shadow_me(caster);
    
    caster->set_fear_target(target);
    
    target->fear_run_away(caster);
    
    target->add_prop(I_HAVE_BEEN_VEKPOSSED, time());    
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
            " is no longer under the effect of Vekpos.\n");
    
        setuid();
        seteuid(getuid());
            
        target->remove_ec_fear_shadow();
        caster->remove_ec_feared_shadow();
    } 
}

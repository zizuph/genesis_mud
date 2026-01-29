/*
 * Support shadow for the rune of welcome cantrip
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "../defs.h"
	
#define OBJ_I_WELCOME_RUNE	   ("_live_i_am_invited")


#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "propchange_base_sh";

int magic_vulnerability;
object wohs_caster;

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_spell_effect_desc("rune of welcome");
    spell_object->set_short("rune of welcome object");

    int power = spell_object->query_spell_effect_power();
    // int duration = power * 10;
    // spell_object->MAX_SPELL_DURATION(MAX_DURATION_CLASS_0, duration);
    // spell_object->set_dispel_time(duration);


}

/* 
 * Function:    query_prop
 * Description: This is the primary function that you should override to
 *              implement the propchange shadow. Make sure to return
 *              the shadow_who->query_prop(prop) result if you don't
 *              want to handle that particular prop.
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);

    if (prop != OBJ_I_WELCOME_RUNE)
    {
        return result;
    }
    
    if (intp(result))
    {
        return max(1, result + 1);
    }
    else 
    {
        return 1;
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
    object caster = spell_object->query_effect_caster();

    if (objectp(target))
    {
        target->catch_tell("You feel yourself marked with a protective rune, " +
           "allowing you passage through the magical forest of Wayreth to the " +
           "Tower of High Sorcery.\n");
        tell_room(environment(target), QCTNAME(target) + " is marked with " +
           "a magical rune.\n", ({ target, caster }));
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
    object target = spell_object->query_effect_target();
    object caster = spell_object->query_effect_caster();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("You feel your protective rune of welcome disappear.\n");
        caster->catch_tell("The rune of welcome dissipates from " +
            COMPOSITE_LIVE(target) + ".\n");
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
        target->catch_tell("You feel the protective rune of welcome begin to "
            + "fade.\n");
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
            + "the protective rune of welcome.\n");
    }    
}

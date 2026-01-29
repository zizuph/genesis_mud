/*
 * Support Shadow for the Warlock Ascendant Step spell
 *
 * Originally created by Petros, modified by Arman (8/2016)
 * and refitted to be used for the warlocks, Nerull 2017
 *
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "../../guild.h"

#ifndef LIVE_I_NO_FOOTPRINTS
#define LIVE_I_NO_FOOTPRINTS   ("_live_i_no_footprints")
#endif

#ifndef LIVE_M_NO_SCRY
#define LIVE_M_NO_SCRY   ("_live_m_no_scry")
#endif

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/propchange_base_sh";

int nofootprint_boost;

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    
    spell_object->set_spell_effect_desc("Ascendant Step");
    spell_object->set_short("ascendand step spell object");

    int power = spell_object->query_spell_effect_power();
    nofootprint_boost = max(1, min(100, power / 3));
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
    
    if (prop != LIVE_I_NO_FOOTPRINTS)
    {
        return result;
    }
    
    if (intp(result))
    {
        return max(1, result + nofootprint_boost);
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

    if (objectp(target))
    {
        target->catch_tell("You start to levitate slightly above "
        +"the ground!\n");

        tell_room(environment(target), QCTNAME(target) 
        + " starts to levitate slightly "
        +"above the ground!\n",
        ({ target }));
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

    if (objectp(target))
    {
        target->catch_tell("Your feet touches the ground as the "
        +"Uraene spell ends.\n");
        
        tell_room(environment(target), QCTNAME(target) 
        + " stops levitating slightly above the ground.\n", ({ target }));
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
        target->catch_tell("You sense your Uraene spell "
        +"begins to fade.\n");
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
        + "the Uraene spell.\n");
    }
}
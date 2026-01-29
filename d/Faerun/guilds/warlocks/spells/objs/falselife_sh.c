/*
*  Base for the false life spell
*
*  Nerull 2018
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
*/

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/shadow_base_sh";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <state_desc.h>

string *health_state;


/*
* Function:    initialize_shadow
* Description: Should do all the initialization effects for this
*              particular shadow. Shadows derived from this one should
*              override this.
*/
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("False Life");
}


int
query_hp()
{
    health_state = SD_HEALTH;

    /* trick ourself into thinking we are almost dead */
    if (file_name(previous_object()) == "/cmd/live/state")
    {
        /*int type = 2;

        if (type == 1)
            return 1;
        else*/
        
        shadow_who->catch_tell(">>>Your actual health is: " 
        + GET_NUM_DESC(shadow_who->query_hp(), 
        shadow_who->query_max_hp(), health_state)+"!<<<\n");
        
        return shadow_who->query_max_hp();
    }

    return shadow_who->query_hp();
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
        target->catch_tell("The spell Urbienc takes effect. You will "
        +"appear unharmed to others even if injured.\n");
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
        target->catch_tell("The spell Urbienc fades away.\n");
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
        target->catch_tell("You sense Urbienc begin to fade.\n");
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
        + "the Urbienc spell.\n");
    }
}
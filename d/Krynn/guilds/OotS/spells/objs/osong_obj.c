/*
 * osong object
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../../defs.h"
#include "/d/Krynn/common/defs.h"

inherit STD_SPELL_SYSTEM + "objs/featherweight_obj";

#include "../../oots_god_descs.h"

#define OOTS_FEATHERWEIGHT_EFFECT "_oots_featherweight_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_oots_featherweight_object_");
    set_short("featherweight spell object");    
    set_long("This is the standard featherweight spell's object. It "
        + "allows a person to lighten their load.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the osong spell.\n");
    set_spell_effect_desc("Song of Freedom");        
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel the burden of your items lessened " +
            "as you receive the blessings of Branchala.\n");
        tell_room(environment(target), QCTNAME(target) + " looks less "
            + "burdened and ready to wander!\n", ({ target }));
    } 

    target->add_prop(OOTS_FEATHERWEIGHT_EFFECT, 1);   
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Your Song of Freedom blessing ends, and you " +
           "feel the weight of your items become more of a burden.\n");
        tell_room(environment(target), QCTNAME(target) + " looks less "
            + "comfortable with " +HIS(target)+ " burdens.\n", 
            ({ target }));
    }

    target->remove_prop(OOTS_FEATHERWEIGHT_EFFECT);
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel your Song of Freedom blessing " +
           "will end soon.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally too tired to maintain "
           + "the Song of Freedom blessing.\n");
    }    
}

/*
 * Function:    query_featherweight_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_featherweight_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are blessed with the Song of Freedom, and your " +
           "burdens feel lighter upon you.\n";
    else
        return capitalize(on->query_pronoun()) + " is blessed by the "
            + "Song of Freedom.\n";
}

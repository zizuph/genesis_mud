/*
 * Stoneskin Object for the Academy of Elemental Arts
 *
 * Created by Petros, September 2009
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "stoneskin_obj";

#define SOHM_STONESKIN_EFFECT "_sohm_stoneskin_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_stoneskin_object_");
    set_short("stoneskin spell object");    
    set_long("This is the standard stoneskin spell's object. It turns "
        + "one's skin to stone.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the stoneskin spell.\n");
    set_spell_effect_desc("stoneskin");    
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("The cladina crumbles to ash as you feel your " +
           "skin absorb the energy of your surroundings, becoming as hard " +
           "as stone.\n");
        tell_room(environment(target), QCTNAME(target) + "'s skin hardens "
            + "and turns to stone.\n", ({ target }));
    }  

    target->add_prop(SOHM_STONESKIN_EFFECT, 1);  
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

    target->remove_prop(SOHM_STONESKIN_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Your skin gradually transforms back "
            + "to normal, losing the hardness it possessed while under "
            + "the effect of the stoneskin spell.\n");
        tell_room(environment(target), QCTPNAME(target) + " skin "
            + "dulls briefly before returning to normal.\n", ({ target }));
    }

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
        target->catch_tell("You feel the magical wards maintaining your stone skin "+
            "transmutation spell beginning to weaken.\n");
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
        caster->catch_tell("Mentally drained, the wards maintaining your " +
           "stone skin transmutation spell fail.\n");
    }    
}

/*
 * Function:    query_stoneskin_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_stoneskin_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your skin has been transmuted to be as hard as stone.\n";
    else
        return capitalize(on->query_pronoun()) + " has skin that has been " +
           "transmuted to be as hard as stone.\n";
}

/*
 * Stoneskin Object for the Academy of Elemental Arts
 *
 * Created by Petros, September 2009
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/stoneskin_obj";

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
                            "created by the lithodermu stoneskin spell.\n");
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
        target->catch_tell("You take the onyx and press it towards your chest. "
            + "Heat radiates from the power you have infused into it and it "
            + "begins to absorb into your skin! As the stone melts into you, "
            + "the onyx surface spreads outwards making your entire skin hard "
            + "as stone.\n");
        tell_room(environment(target), QCTNAME(target) + "'s skin hardens "
            + "and turns to stone.\n", ({ target }));
    }    
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

    if (objectp(target))
    {
        target->catch_tell("Your skin gradually transforms back "
            + "to normal, losing the hardness it possessed while under "
            + "the effect of lithodermu.\n");
        tell_room(environment(target), QCTPNAME(target) + " skin "
            + "shimmers briefly and returns to normal.\n", ({ target }));
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
        target->catch_tell("You feel the earthly elemental energy slowly "
            + "begin to seep out of your skin.\n");
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
        caster->catch_tell("Mentally drained, you lose control of "
            + "the earthly elemental energies sustaining the "
            + "power of lithodermu.\n");
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
        return  "Your skin is infused with earth energies and is as "
            + "hard as a rock.\n";
    else
        return capitalize(on->query_pronoun()) + " has skin that looks tough "
            + "and stoney.\n";
}

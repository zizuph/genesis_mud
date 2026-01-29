/*
 * Light Spell Object for the Academy of Elemental Arts
 *
 * Created by Petros, September 2009
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "../defs.h"

inherit "/d/Genesis/specials/std/spells/obj/light_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_pyrofosti_light_object_");
    set_short("pyrofosti light spell object");    
    set_long("This is the object for the light spell of the Academy "
        + "of Elemental Arts.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the "
        + "pyrofosti light spell.\n");
    set_spell_effect_desc("brighten room");
    
    set_dispel_time(600 + random(600) + random(600));
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();

    if (objectp(caster))
    {
        caster->catch_tell("You direct the energies of fire into the "
            + "crystal and cause it to shine brightly. The quartz shard "
            + "suddenly shatters causing the light to escape and surround "
            + "you, making the room brighter.\n");
        tell_room(environment(caster), QCTNAME(caster) + "'s fist becomes "
            + "brighter and brighter until a brilliant burst of light "
            + "escapes from " + caster->query_possessive() + " hands and "
            + "surrounds " + caster->query_objective() + ", making the "
            + "room brighter.\n",
            ({ caster }) );
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
        target->catch_tell("The luminescence surrounding you fades away.\n");
        tell_room(environment(target), "The luminescence surrounding "
            + QTNAME(target) + " fades away.\n", ({ target }));
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
        target->catch_tell("You sense that your control over the light "
            + "surrounding you begins to weaken.\n");
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
        caster->catch_tell("Mentally drained, your control over the pyrofosti "
            + "effect is lost.\n");
    }    
}

/*
 * Function:    query_light_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_light_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are surrounded by luminescence.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by light.\n";
}

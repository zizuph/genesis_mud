/*
 * Light Spell Object for the Elemental Worshippers of Calia
 *
 * Created by Petros, December 2010
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
    set_long("This is the object for the light spell of the Elemental "
        + "Worshippers of Calia.\n");

    add_prop(OBJ_M_NO_DROP, 1);
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
        caster->catch_tell("As you complete the prayer calling out to "
            + "Lord Pyros, a small intense flame emerges beside you and "
            + "begins hovering next to you. It brightens your "
            + "surroundings with its magical light.\n");
        tell_room(environment(caster), "As " + QTNAME(caster) + " stops "
            + "praying, a small intense flame emerges beside " 
            + caster->query_objective()
            + " and begins hovering next to " + caster->query_objective()
            + ", making the surroundings brighter.\n",
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
        target->catch_tell("The small intense flame of pyrofosti fades "
            + "away.\n");
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
        target->catch_tell("The small intense flame of pyrofosti begins "
            + "flickering. You sense it will extinguish soon.\n");
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
        caster->catch_tell("Mentally drained, your control over the "
            + "pyrofosti gift is lost.\n");
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
        return  "You are surrounded by luminescence from a small intense "
            + "flame.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by light "
            + "from a small intense flame.\n";
}

/*
 * Priests of Takhisis PBless Object.
 *
 * This is the spell object for the 'pbless' spell for the Priests of
 * Takhisis.
 * It is based off the stone skin spell object.
 *
 * Created by Navarre, May 2013.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/stoneskin_obj";

#include <macros.h>
#include "../../defs.h"
#include "/d/Ansalon/common/defs.h"


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_pot_pbless_object_");
    set_short("pbless object");    
    set_long("This is the pbless object. It protects the priest " +
             "from damage.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the pot pbless spell.\n");
    set_spell_effect_desc("pbless");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{
    return POT_SPELL_OBJS + "pbless_dam_mod";
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    // TODO: See if we can just delete this function - we already give this
    //       Description in the resolve function in pbless.
    
    // object target = query_effect_target();

    // if (!objectp(target))
    // {
        // return;
    // }
    // object caster = query_effect_caster();
    
    // string caster_message = "As you complete your prayer to Lady Gu, "
        // + "you sense earth tremble and stir stir as she grants the "
        // + "the strength of the earth for your use. ";
    // string target_message = "Sand springs from the ground and swirls "
        // + "around you before quickly infusing the pores of your skin "
        // + "with their essence. Your skin transform and assumes "
        // + "a diamond-like texture.\n";
    // string watcher_message = "Sand springs from the ground and swirls "
        // + "around " + QTNAME(target) + " before quickly infusing the "
        // + "pores of " + target->query_possessive() + " skin with their "
        // + "essence. " + QCTPNAME(target) + " skin transforms and assumes "
        // + "a diamond-like appearance.\n";
    // if (target == query_effect_caster())
    // {
        // caster->catch_msg(caster_message + target_message);
    // }
    // else
    // {
        // caster->catch_msg(caster_message + "\n");
        // target->catch_msg(target_message);
    // }
    // tell_room(environment(target), watcher_message, ({ target, caster }));
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

    if (!objectp(target))
    {
        return;
    }
    
    // We only want to tell the player affected as a blessing is nothing
    // visible.
    target->catch_tell("You feel the blessing of the Queen of Darkness " +
                       "dissipate making you more receptable to attacks " +
                       "once more.\n");
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
    
    if (!objectp(target))
    {
        return;
    }
    target->catch_tell("You feel the blessing of the Dark Queen starting " +
                       "to weaken.\n");
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
        caster->catch_tell("Being mentally drained, you lose touch with the " +
                           "Dark Queen for a brief moment and feel her " +
                           "blessing on you disappear.\n");
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
    string description;
    
    if (for_obj == on)
    {
        description = "You are fortified by the power of Takhisis.\n";
    }    
    else
    {
        description = C(HE(on)) + " is fortified by the power of Takhisis.\n";
    }
    return description;
}

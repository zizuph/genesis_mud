/*
 * Earth Shield for the Schirmo Spell for the Elementalists of Calia
 *
 * Created by Petros, January 2013
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "stoneskin_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_schirmo_earth_object_");
    set_short("schirmo earth shield object");    
    set_long("This is the schirmo earth shield object. It absorbs "
        + "incoming damage.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the schirmo elemental shield spell.\n");
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("schirmo earth shield");    
    return ::setup_spell_effect();
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{
    return ELEMENTALIST_SPELL_OBJS + "earthshield_dam_mod";
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

    if (!objectp(target))
    {
        return;
    }
    object caster = query_effect_caster();
    
    string caster_message = "As you complete your prayer to Lady Gu, "
        + "you sense the earth tremble and stir as she grants the "
        + "strength of the earth for your use. ";
    string target_message = "Sand springs from the ground and swirls "
        + "around you before quickly infusing the pores of your skin "
        + "with their essence. Your skin transforms and assumes "
        + "a diamond-like texture.\n";
    string watcher_message = "Sand springs from the ground and swirls "
        + "around " + QTNAME(target) + " before quickly infusing the "
        + "pores of " + target->query_possessive() + " skin with their "
        + "essence. " + QCTPNAME(target) + " skin transforms and assumes "
        + "a diamond-like appearance.\n";
    if (target == query_effect_caster())
    {
        caster->catch_msg(caster_message + target_message);
    }
    else
    {
        caster->catch_msg(caster_message + "\n");
        target->catch_msg(target_message);
    }
    tell_room(environment(target), watcher_message, ({ target, caster }));
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
    target->catch_tell("Your skin gradually transforms back "
        + "to normal, losing the hardness it possessed while under "
        + "the gifts of Lady Gu.\n");
    tell_room(environment(target), QCTPNAME(target) + " skin "
        + "shimmers briefly and returns to normal.\n", ({ target }));
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
    target->catch_tell("You feel the strength of diamond-like texture "
        + "of your skin start to ebb.\n");
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
            + "the earthly elemental powers sustaining the "
            + "schirmo gift of Lady Gu.\n");
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
        return  "Your skin is infused with earth energies and possesses "
            + "a diamond-like texture.\n";
    else
        return capitalize(on->query_pronoun()) + " has skin that looks tough "
            + "and has the appearance of diamond.\n";
}

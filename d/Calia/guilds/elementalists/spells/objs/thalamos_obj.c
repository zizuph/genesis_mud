/*
 * Undead Ward Shield for the Thalamos Spell 
 *
 * Created by Arman, April 2022
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
    set_name("_thalamos_object_");
    set_short("thalamos stoneskin object");    
    set_long("This is the thalamos stoneskin object. It absorbs "
        + "incoming damage from undead only.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the thalamos stoneskin "+
                            "spell.\n");
    set_spell_effect_desc("thalamos undead ward");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{
    return ELEMENTALIST_SPELL_OBJS + "thalamos_dam_mod";
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
    
    string caster_message = "";
    string target_message = "From the corner of sight shimmering trails "
        + "twirl into existence and envelop you in shadow and silver.\n";
    string watcher_message = "From the corner of sight shimmering trails "
        + "twirl into existence and envelop " + QTNAME(target) 
        + " in shadow and silver.\n";

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
    target->catch_tell("The shimmering trails surrounding you " +
        "fade and vanish.\n");
    tell_room(environment(target), "The shimmering trails surrounding " +
        QTNAME(target) + " fade and vanish.\n", ({ target }));
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
    target->catch_tell("The shimmer trails enveloping you fade briefly. " +
        "You sense their protection will expire soon.\n");
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
            + "your ward against the Soulless.\n");
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
        return  "You are enveloped by shimmering trails of shadow and silver.\n";
    else
        return capitalize(on->query_pronoun()) + " is enveloped by shimmering " +
            "trails of shadow and silver.\n";
}

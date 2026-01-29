/*
 * Haste Object for the phoenix-bladed axe
 *
 * Created by Arman, Jan 2021
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#define HASTE_EFFECT "_phoenix_haste_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_phoenix_haste_object_");
    set_short("haste spell object");    
    set_long("This is the standard haste spell's object. It makes "
        + "one faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the haste spell.\n");
    set_spell_effect_desc("haste");  

    // 15 minute duration
    set_dispel_time(900);  

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
        target->catch_tell("The enchantment of the phoenix-bladed axe takes effect, " +
            "and you feel the winds rise around you, enhancing your movement and " +
            "increasing your speed.\n");
        tell_room(environment(target), "You perceive " +QTNAME(target) + " moving "
            + "and reacting a lot more quickly than before.\n", ({ target }));
    }      

    target->add_prop(HASTE_EFFECT, 1);  
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

    target->remove_prop(HASTE_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The winds around you drop and you feel the " +
            "enchantment of the phoenix-bladed axe expire.\n");
        tell_room(environment(target), "You perceive " +QTNAME(target) + " moving "
            + "and reacting more slowly than before.\n", ({ target }));
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
        caster->catch_tell("Mentally drained, the enchantment of the " +
           "phoenix-bladed axe expires.\n");
    }    
}


/*
 * Haste Object for the Academy of Elemental Arts
 *
 * Created by Petros, September 2009
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#define SOHM_HASTE_EFFECT "_sohm_haste_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_haste_object_");
    set_short("haste spell object");    
    set_long("This is the standard haste spell's object. It makes "
        + "one faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the haste spell.\n");
    set_spell_effect_desc("haste");  

    set_dispel_time(1200);  

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
        target->catch_tell("Your heart beats faster as the haste spell takes effect, " +
            "and you perceive the world as moving much more slowly around you.\n");
        tell_room(environment(target), "You perceive " +QTNAME(target) + " moving "
            + "and reacting a lot more quickly than before.\n", ({ target }));
    }      

    target->add_prop(SOHM_HASTE_EFFECT, 1);  
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

    target->remove_prop(SOHM_HASTE_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Your heart beat returns to normal as your haste spell expires, " +
            "and you perceive the world at a normal speed now.\n");
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
        target->catch_tell("You feel the illusions maintaining your haste "+
            "spell beginning to weaken.\n");
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
        caster->catch_tell("Mentally drained, the illusions maintaining your " +
           "haste spell fail.\n");
    }    
}


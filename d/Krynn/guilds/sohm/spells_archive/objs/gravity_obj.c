/*
 * Haste Object for the Gravity spell
 *
 * 
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#define SOHM_GRAVITY_EFFECT "_sohm_gravity_effect"

/*
 * Function:    convert_aid_to_quickness
 * Description: LIVE_I_QUICKNESS uses a system that is based on a
 *              number between 1-500. Haste combat aid is based on
 *              calculation of (haste / 500 - haste). We simply
 *              convert the combat aid for the aid into the haste
 *              number that can be plugged in.
 */
public int
convert_caid_to_haste(object player, int aid)
{ 
    int quickness = ::convert_caid_to_haste(player, aid);

    // This is an anti-haste spell, so it provides negative quickness
    // of equivalent value to a positive haste spell of the same caid

    return -quickness;
}

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_gravity_object_");
    set_short("gravity spell object");    
    set_long("This is the gravity spell's object. It allows "
        + "a person to burden an enemy.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the gravity spell.\n");
    set_spell_effect_desc("gravity"); 

}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    int power = query_spell_effect_power();

    // Power determines how long the spell lasts
    // trans earth skills: 60,50   100,100
    // 100 stat  duration:   35      38  
    // 200 stat  duration:   42      47     
    int duration = ftoi(itof(power));
    set_dispel_time(duration);

    // DEBUG("Gravity power: " +power+ ", duration: "+duration+ ".");

    return result;
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
        target->catch_tell("You feel a powerful force from the earth pull at you, making " +
           "your burdens feel heavier.\n");
        tell_room(environment(target), QCTNAME(target) + " looks more burdened, as if an "
            + "invisible force was forcing " +HIM(target)+ " down.\n", 
            ({ target }));
    } 

    target->add_prop(SOHM_GRAVITY_EFFECT, 1);   
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

    target->remove_prop(SOHM_GRAVITY_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The powerful force pulling you down vanishes. You " +
              "feel your burdens lessen considerably.\n");
        tell_room(environment(target), "The powerful force pulling " +QTNAME(target) + 
            " down vanishes, no longer burdening " +HIM(target)+ ".\n", ({ target }));
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
        caster->catch_tell("You are mentally unable to maintain "
            + "the gravity spell.\n");
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
        return  "You are struggling with forces pulling you towards the ground.\n";
    else
        return capitalize(on->query_pronoun()) + " is struggling with forces "
            + "pulling " +HIM(on)+ " down.\n";
}


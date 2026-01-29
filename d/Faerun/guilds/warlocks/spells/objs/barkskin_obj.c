/*
 * Barkskin Object for the Warlocks.
 *
 * Originally created by Petros, September 2009, 
 * used by Nerull, 2017
 */
 
#pragma strict_types
#pragma save_binary
#include <macros.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/stoneskin_obj";

#define BARKSKIN_EFFECT "_barkskin_effect"


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_barkskin_object_");
    set_short("barkskin spell object");    
    set_long("This is the standard barkskin spell's object. It turns "
        + "one's skin to be as hard as bark.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the barkskin spell.\n");
    set_spell_effect_desc("Barkskin");    
}


/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return WARLOCK_SPELLOB_DIR + "barkskin_dam_mod_base_obj";
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
        target->catch_tell("Your skin hardens and turns "
        +"into bark!\n");
           
        tell_room(environment(target), QCTNAME(target) + "'s skin hardens "
            + "and turns into bark.\n", ({ target }));
    }  
    
    target->add_prop(BARKSKIN_EFFECT, 1);
    target->add_prop(SHIELD_ON, 1); 
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
    target->remove_prop(BARKSKIN_EFFECT);
    target->remove_prop(SHIELD_ON);
    if(target->query_ghost())
        return;
    if (objectp(target))
    {
        target->catch_tell("Your skin turns back to normal.\n");
            
        tell_room(environment(target), QCTPNAME(target) + " skin "
            + "returns back to normal.\n", ({ target }));
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
        target->catch_tell("You feel the Treashi spell is starting "
        +"to fade.\n");
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
        caster->catch_tell("Mentally fatigued, the Treashi spell "
        +"can no longer be maintained.\n");
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
        return  "Your skin has been transmuted to be as hard as bark.\n";
    else
        return capitalize(on->query_pronoun()) + " has skin that has been " +
           "transmuted to be as hard as bark.\n";
}
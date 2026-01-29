/*
 * Resilience Object for the Vampires.
 *
 * Originally created by Petros, September 2009, 
 * used by Nerull, 2021
 */
 
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/stoneskin_obj";
 
#pragma strict_types
#pragma save_binary
#include <macros.h>
#include "../../guild.h"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_resilience_object");
    set_short("resilience spell object");    
    set_long("This is the standard resilience spell's object. It turns "
        + "one's skin to absorb more damage.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the resilience spell.\n");
    set_spell_effect_desc("Resilience");    
}


/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return VAMPIRES_SPELLOB_DIR + "resilience_dam_mod_base_obj";
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
        target->catch_tell("By the power of the blood, "
        +"your skin is supernaturally "
        +"enhanced to absorb more incoming damage.\n");
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

    if(target->query_ghost())
        return;
        
    if (objectp(target))
    {
        target->catch_tell("Your skin turns back to normal.\n");
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
        target->catch_tell("You feel the Resilience spell is starting "
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
        caster->catch_tell("Mentally fatigued, the Resilience spell "
        +"can no longer be maintained.\n");
    }    
}

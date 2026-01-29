/* 
 * pbless object - blessed by the dark forces
 * (protection from good)
 * 2004-07-06   Cotillion
 *  Fixed runtime in hit_me
 * 2016-08-02 Updated to new magic system - Arman
 *  Converted it to the standard stoneskin base
 */

#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "stoneskin_obj";

#define BLESS_SUBLOC "pot_bless_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_pbless_object_");
    set_short("PoT pbless spell object");    
    set_long("This is the PoT bless spell object, based on the standard " +
        "stoneskin spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the pbless spell.\n");
    set_spell_effect_desc("protection from good");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return GUILDDIRSPELL + "obj/pblessing_dam_mod_obj_base";
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
        target->catch_tell("You invoke Takhisis' blessing against the " +
           "forces of good. You feel a warm touch over your body and you " +
           "know you are less vulnerable to attacks by those good aligned.\n");
        tell_room(environment(target), QCTNAME(target) + " is protected by the " +
           "dark blessings of Takhisis.\n", ({ target }));
    }  

    target->add_prop(BLESS_SUBLOC, 1);  
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
    object caster = query_effect_caster();

    if(target->query_ghost())
        return;
    
    if (objectp(caster))
    {
        caster->catch_tell("You feel the touch of the Queen of Darkness " +
        "leave you, and you are more vulnerable to the corrupted forces of " +
        "good.\n");
    }

/*
    if (objectp(target))
    {
        tell_room(environment(target), QCTNAME(target) + " is no "
            + "longer protected by the blessings of Takhisis.\n", ({ target }));
    }
*/

    target->remove_prop(BLESS_SUBLOC);
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
        target->catch_tell("You feel the blessings of Takhisis begin to wane.\n");
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
        caster->catch_tell("Mentally drained, the blessings of Takhisis " +
           "leave you.\n");
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
        return  "You are protected by the blessings of the Dark Queen.\n";
    else
        return capitalize(on->query_pronoun()) + " is protected by the " +
            "dark blessings of Takhisis.\n";
}


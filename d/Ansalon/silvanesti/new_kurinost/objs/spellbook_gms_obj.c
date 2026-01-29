/*
 * Greater Magic Shield Object for WoHS
 *
 * Created by Arman, 2016
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/stoneskin_obj";

#define SOHM_GREATER_MAGIC_SHIELD_EFFECT "_kurinost_advanced_magic_shield_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_kurinost_greater_magic_shield_object_");
    set_short("greater magic shield spell object");    
    set_long("This is the magic shield spell's object. It "
        + "reduces damage directed at the caster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the magic shield spell.\n");
    set_spell_effect_desc("shield of magical force");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return "/d/Krynn/guilds/sohm/spells/objs/greater_shield_dam_mod_obj_base";
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
        target->catch_tell("A shimmering shield of magical force surrounds you, " +
              "protecting you from damage.\n");
        tell_room(environment(target), "A shimmering shield of magical force surrounds " +
            QTNAME(target) + ".\n", ({ target }));
    }    

    target->add_prop(SOHM_GREATER_MAGIC_SHIELD_EFFECT, 1);

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

    target->remove_prop(SOHM_GREATER_MAGIC_SHIELD_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The shimmering shield of magical force dissipates.\n");
        tell_room(environment(target), "The shimmering shield of magical force " +
            "surrounding " +QTNAME(target) + " dissipates.\n", ({ target }));
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
        target->catch_tell("You feel the magical wards maintaining your magic shield "+
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
        caster->catch_tell("Mentally drained, the wards maintaining your " +
           "magic shield spell fail.\n");
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
        return  "A shimmering shield of magical force surrounds you.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by a " +
            "shimmering shield of magical force.\n";
}

/* 
 * obless object - blessed by divine forces
 */

#include "/d/Ansalon/common/defs.h"
#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

inherit STD_SPELL_SYSTEM + "objs/stoneskin_obj";

#include "../../oots_god_descs.h"

#define BLESS_SUBLOC "OotS_bless_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_obless_object_");
    set_short("OotS obless spell object");    
    set_long("This is the OotS bless spell object, based on the standard " +
        "stoneskin spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the " +
        "obless spell.\n");
    set_spell_effect_desc("protection from evil");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return OOTS_SPELL_OBJS + "oblessing_dam_mod_obj_base";
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
        target->catch_tell("You beseech the blessings of " +
           oots_god_name(target) + " to protect against the forces of " +
           "evil. You feel a warm touch over your body and you know " +
           "you are less vulnerable to attacks by those evil aligned.\n");
        tell_room(environment(target), QCTNAME(target) + " is protected " +
           "by the divine blessings of "+oots_god_name(target)+".\n", 
           ({ target }));
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
        caster->catch_tell("You feel the blessings of " +
           oots_god_name(caster) + " " + "leave you, and you are more " +
           "vulnerable to the dark forces of evil.\n");
    }

/*
    if (objectp(target))
    {
        tell_room(environment(target), QCTNAME(target) + " is no "
            + "longer protected by the blessings of "+
            oots_god_name(target)+".\n", ({ target }));
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
        target->catch_tell("You feel the blessings of " + 
           oots_god_name(target) + " begin to wane.\n");
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
        caster->catch_tell("Mentally drained, the blessings of " + 
           oots_god_name(caster) + " leave you.\n");
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
        return  "You are protected from evil by the blessings of "
                +oots_god_name(on)+".\n";
    else
        return capitalize(on->query_pronoun()) + " is protected by the " +
            "divine blessings of "+oots_god_name(on)+".\n";
}


/* 
 * ondo object - channelling the protection of Aule
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Shire/common/defs.h"
#include "../../herald.h"

inherit "/d/Genesis/specials/new/magic/spells/objs/stoneskin_obj";

#define BLESS_SUBLOC "herald_ondo_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_ondo_object_");
    set_short("ondo spell object");    
    set_long("This is the herald ondo spell object, based on the standard " +
        "stoneskin spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the " +
        "herald ondo spell.\n");
    set_spell_effect_desc("Aule's embrace");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return HERALD_SPELLS_OBJ + "ondo_dam_mod_obj_base";
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
        target->catch_tell("You feel the indomitable strength of the " +
            "earth surge through your body.\n");
        tell_room(environment(target), QCTPNAME(target) + " body " +
           "hardens, becoming as tough as the earth.\n", 
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
        caster->catch_tell("You cease channelling Aule, and your " +
            "body loses its hardness.\n");
    }

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
        target->catch_tell("You feel you won't be able to maintain " +
            "your channeling of Aule for much longer.\n");
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
        caster->catch_tell("Mentally drained, you cease channelling " +
            "Aule.\n");
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
        return  "Your body is hardened by the earthy embrace of Aule.\n";
    else
        return capitalize(on->query_pronoun()) + " looks " +
            "hardened, with a distinct earthy aspect.\n";
}


/*
 * Spell Resistance Object for the Elemental Guilds of Calia
 *
 * This is the spell object based on the standard Genesis Magic System 
 * Resistance spell.
 *
 * Created by Petros, December 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "resistance_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_unteristi_object_");
    set_short("unteristi spell object");    
    set_long("This is the standard resistance spell's object. It protects "
        + "one against certain elements.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the unteristi spell.\n");
    set_spell_effect_desc("magic resistance");    
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();
    object target = query_effect_target();
    
    if (objectp(caster))
    {
        caster->catch_tell("You complete your prayer to the Elementals and "
            + "sense that your request has been heard. A dazzling array of "
            + "lights appear in your hands and expand to surround you "
            + "completely. You feel more resistant.\n");
        tell_room(environment(caster), QCTNAME(caster) + " is surrounded "
            + "by a dazzling array of lights.\n", ({ caster }));
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

    if (objectp(target))
    {
        target->catch_tell("You sense that the magical protection you received "
            + "through the gift of unteristi has faded away.\n");
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
        target->catch_tell("You feel the gift of unteristi begin to fade "
            + "away.\n");
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
            + "the gift of unteristi.\n");
    }    
}

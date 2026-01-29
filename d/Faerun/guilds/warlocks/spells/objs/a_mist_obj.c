/*
 * Standard Spell Resistance Object
 *
 * This is the spell object for the standard Genesis Magic System Resistance
 * spell.
 *
 * Originaly created by Petros, March 2010, used by Nerull 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/resistance_obj";

/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_protect_air_fire_object_");
    set_short("ward against air and fire object");
    set_long("This is the standard resistance spell's object. It protects "
        + "one against certain elements.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created to protect against air and fire.\n");
        
    set_spell_effect_desc("Armor Of Mist");
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
        target->catch_tell("You are surrounded by grey mist. You are now warded "
        +"from air and fire magic.\n");
        
        tell_room(environment(target), QCTNAME(target) + " is suddenly surrounded "
        +"by a grey mist.\n", ({ target }));
        
        target->add_prop(MR_SHIELD_ON, 1);
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
        target->catch_tell("You feel your ward against air and fire "
        +"magic disappear.\n");  
        
        tell_room(environment(target), QCTNAME(target) + " is no longer " 
        +"enveloped by a grey mist.\n", ({ target }));
        
        target->remove_prop(MR_SHIELD_ON);
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
        target->catch_tell("You feel Urluir "
        +"begins to fade.\n");
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
            + "the Urluir spell.\n");
    }
}
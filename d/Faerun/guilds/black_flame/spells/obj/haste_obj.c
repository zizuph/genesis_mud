/*
* This is the spell object based on the the standard Genesis Magic
* System Haste spell.
*
* Originally created by Petros, December 2010
*/

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/haste_obj";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../../guild.h"

/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_frenzy_object");
    set_short("frenzy spell object");
    set_long("This is the standard haste spell's object. It causes "
        + "one to move faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created by the frenzy spell.\n");
        
    set_spell_effect_desc("Frenzy");
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
        target->catch_tell("Agitated like a raging fire of Kossuth, your "
		+"muscles tenses up like coils and burts out in renewed "
		+"power.\nYou move faster.\n");
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
        target->catch_tell("Your muscles winds down as the "
		+"raging fire within dissipates.\nYou move slower.\n");
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
        target->catch_tell("You sense that Frenzy is "
        +"starting to fade off.\n");
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
            + "Frenzy.\n");
    }
}
/*
 * This is the spell object based on the the standard Genesis Magic
 * System Haste spell.
 *
 * Originally created by Petros, December 2010
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/haste_obj";


/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_warpreality_object_");
    set_short("warpreality spell object");
    set_long("This is the standard haste spell's object. It causes "
        + "one to move faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created by the warp-reality spell.\n");
        
    set_spell_effect_desc("Warp Reality");

    set_dispel_time(1800);
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
        target->catch_tell("With a discree gesture of your arms, you warp "
        +"the reality around you, slowing it considerably.\n");
            
        tell_room(environment(target), QCTNAME(target) 
        + " seems to start moving faster!\n", ({ target }));
        
        target->add_prop(HASTE_ON, 1);
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
        target->catch_tell("The reality around you crawls back to "
        +"normal pace.\n");
            
        tell_room(environment(target), QCTNAME(target) + " seems to slow "
        + "down.\n", ({ target }));
        
        target->remove_prop(HASTE_ON);
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
        target->catch_tell("You sense that the reality around "
        +"you starts to crawl back to normal pace.\n");
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
            + "Uralane.\n");
    }
}
/*
 * Nerull 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/spell_obj_base";

#define INVIS_LEVEL 10

// Global Variables
int g_invis_amount = INVIS_LEVEL;

/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_eldritch_sight_object_");
    set_short("eldritch sight spell object");

    set_long("This is the standard dark-sight spell's object. It grants "
        + "vision to see in darkness.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created by the eldritch sight spell.\n");

    set_spell_effect_desc("Eldritch Sight");

}


/*
* Function:    setup_spell_effect
* Description: This is called to set up all the things for the
*              spell. Must call the parent's setup_spell_effect
*              in order to get the maintainence stuff.
*/
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    object target = query_effect_target();

    int current_see_invis = target->query_prop(LIVE_I_SEE_INVIS);

    if (g_invis_amount + current_see_invis >= 100)
    {
        // don't allow someone to see to 100. That is wizard-style see invis.
        // assume that they're not at 99 already.
        g_invis_amount = max(1, 100 - current_see_invis);
    }

    //target->inc_prop(LIVE_I_SEE_INVIS, g_invis_amount);
    target->inc_prop(LIVE_I_SEE_DARK, g_invis_amount);

    return result;
}


public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);

    if (!result)
    {
        return result;
    }

    //query_effect_target()->dec_prop(LIVE_I_SEE_INVIS, g_invis_amount);
    query_effect_target()->dec_prop(LIVE_I_SEE_DARK, g_invis_amount);
    
    return 1;
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
        target->catch_tell("Your eyes tingle with a strange "
        +"sensation. You can now see in darkness.\n");
        
        target->add_prop(ELDRITCH_SIGHT_ON, 1);
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
            target->catch_tell("The tingling in your eyes "
            +"fades away.\n");
            
            target->remove_prop(ELDRITCH_SIGHT_ON);
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
        target->catch_tell("You sense your Urhavol spell "
        + "is starting to fade.\n");
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
        + "Urhavol.\n");
    }
}
/* 
 * peyes - dragon eyes.
 *
 * This is the spell object for the standard Genesis Magic System Dark
 * vision spell. It provides light as a duration spell effect, and 
 * continually drains mana.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 *
 * 2022-01-19 Zizuph - increase level calculations to account for
 *                     change of CAID in power from 100 to 20.
 *                     moved to default spell duration.
 *
 *
  */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";

#define EYES_SUBLOC "eyes"

object gSublocObj;
int gDark;
int see_invis;
int alarm;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name(EYES_ID);
    set_short("peyes spell object");    
    set_long("This is the standard darkvision spell's object. It grants "
        + "sight in darkness.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the darkvision spell.\n");
    set_spell_effect_desc("peyes");
    
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

    int power = query_spell_effect_power();

    set_dispel_time(get_default_spell_time());

    object target = query_effect_target();
    object caster = query_effect_caster();

    switch (caster->query_priest_level())
    {
        case 2:        // ancient dragon
    	    gDark  = min(5, ftoi(itof(power) / 20.0));
    	    break;
    	case 1:         // aged dragon
    	    gDark  = min(3, ftoi(itof(power) / 20.0));
    	    break;
    	default:         // adult dragon
    	    gDark  = 1;
    }

    target->change_prop(LIVE_I_SEE_DARK,
        target->query_prop(LIVE_I_SEE_DARK) + gDark);
    if (gDark > 1)
    {
        see_invis = 1;
        target->change_prop(LIVE_I_SEE_INVIS,
            target->query_prop(LIVE_I_SEE_INVIS) + gDark);
    }

    gSublocObj = target->query_subloc_obj(EYES_SUBLOC);

    target->add_subloc(EYES_SUBLOC, TO);

    // target->catch_tell("Darkvision level: " +gDark+ ".\n");

    return result;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    query_effect_target()->change_prop(LIVE_I_SEE_DARK,
        query_effect_target()->query_prop(LIVE_I_SEE_DARK) - gDark);

    if(see_invis)
       query_effect_target()->change_prop(LIVE_I_SEE_INVIS,
           query_effect_target()->query_prop(LIVE_I_SEE_INVIS) - gDark);

    query_effect_target()->remove_subloc(EYES_SUBLOC);

    if (objectp(gSublocObj))
        query_effect_target()->add_subloc(EYES_SUBLOC, gSublocObj);
    
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
        target->catch_tell("You close your eyes in pain for a moment. " +
	"When you open them you see things better.\n");

        tell_room(environment(target), QCTNAME(target)+ " closes "+
        HIS(target)+" eyes for a moment. When they reopen, they look " +
        "strikingly reptilian.\n", ({ target }), target);
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
        target->catch_tell("You feel the prayer improving your vision begin to wane.\n");
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
        target->catch_tell("You close your eyes in pain for a moment. " +
	"When you open them your vision returns to normal.\n");
        tell_room(environment(target), QCTNAME(target)+ " closes "+
        HIS(target)+" eyes for a moment. When they reopen, they no " +
        "longer look reptilian.\n", ({ target }), target);
    }
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You have the eyes of a dragon.\n";

    return C(HIS(me)) + " eyes look like the eyes of a dragon.\n";
}


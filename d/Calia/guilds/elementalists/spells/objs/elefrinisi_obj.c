/*
 * Elefrinisi Shadow for the Elemental Guilds of Calia
 *
 * This is the spell shadow based on the standard featherweight effect.
 *
 * Created by Petros, December 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "featherweight_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_elefrinisi_featherweight_object_");
    set_short("elefrinisi featherweight spell object");    
    set_long("This is the object for the featherweight spell of the Elemental "
        + "Worshippers of Calia.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the "
        + "elefrinisi featherweight spell.\n");
    set_spell_effect_desc("lighten burdens");
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
    	if (target->is_elemental_cleric())
    	{
	        target->catch_tell("Your prayers are answered and everything you "
	            + "carry seems lighter as if the pull of the earth itself has "
	            + "alleviated your burdens.\n");
	    }
	    else
	    {
	    	target->catch_tell("Everything you carry seems lighter as if the "+
	    	    "pull of the earth itself has alleviated your burdens.\n");
	    }
        tell_room(environment(target), QCTNAME(target) + " seems to have a "
            + "heavy burden lifted from " + target->query_objective() + ".\n", 
            ({ target }));
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
    	if (target->is_elemental_cleric())
    	{
	        target->catch_tell("The blessings of the gift of elefrinisi "
	            + "subside, and you once again feel the full weight of "
	            + "your belongings.\n");
	    }
	    else
	    {
	    	target->catch_tell("The blessings of the elemental gift "
	            + "subside, and you once again feel the full weight of "
	            + "your belongings.\n");
	    }
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "weighed down by something.   \n", ({ target }));
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
    	if (target->is_elemental_cleric())
    	{
	        target->catch_tell("You sense the gift of elefrinisi is about "
	            + "to expire.\n");
	    }
	    else
	    {
	    	target->catch_tell("You send the presence of Lady Gu's uplifting "+
	    	    "gift is about to expire.\n");
	    }    
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
            + "the gift of elefrinisi.\n");
    }    
}

/*
 * Function:    query_featherweight_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_featherweight_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You sense the presence of Lady Gu's gift uplifting "
            + "your burdens.\n";
    else
        return capitalize(on->query_pronoun()) + " has the posture of "
            + "one who is unburdened.\n";
}

/*
 * Propchange Shadow for the Elemental Guilds of Calia
 *
 * This is the spell shadow based on the standard Genesis Magic System 
 * Propchange spell.
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

inherit "/d/Genesis/specials/std/spells/obj/propchange_base_sh";

int magic_vulnerability;
object ec_caster;

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

/*
 * Function   : remove_shadow
 * Description: Removes the shadow without removing the shadowed object.
 */
public void 
remove_shadow()
{
    object caster = ec_caster;

    caster->remove_prop("_kato_prop");
    caster->remove_prop("_live_i_cast_kato");
    destruct();
}

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_spell_effect_desc("lower resistance");
    spell_object->set_short("lower resistance prayer object");
    spell_object->set_name("_kato_object_");
    spell_object->add_prop(OBJ_M_NO_DROP,1);

    ec_caster = spell_object->query_effect_caster();

    int power = spell_object->query_spell_effect_power();
    
    if (ec_caster->query_prop(CONDUIT_PENALTY) == 3)
		magic_vulnerability = -22;
	else
		magic_vulnerability = -45;

    int duration = power / 3; 
    duration = (duration / 2) + random(duration / 2) + random(duration / 2);
    spell_object->set_dispel_time(duration);
}

/*
 * Function     : remove_propchange_shadow
 * Description  : Easy way to remove propchange shadow. 
*/ 
public void 
remove_propchange_shadow()
{
    find_player("arman")->catch_msg("[kato] remove propchange called\n");

    object caster = ec_caster;

    if(!objectp(caster))
        find_player("arman")->catch_msg("[kato] no caster object\n");

    caster->remove_prop("_kato_prop");
    caster->remove_prop("_live_i_cast_kato");
    remove_spell_shadow();
}

/* 
 * Function:    query_prop
 * Description: This is the primary function that you should override to
 *              implement the propchange shadow. Make sure to return
 *              the shadow_who->query_prop(prop) result if you don't
 *              want to handle that particular prop.
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
    string element; 

    element = ec_caster->query_prop("_kato_prop");
 
    string resistance_prop = "_obj_magic_i_res_" + element;

    if (prop != resistance_prop)
    {
        return result;
    }
    
    if (intp(result))
    {
        return magic_vulnerability;
    }
    else 
    {
        return 1;
    }
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    object target = spell_object->query_effect_target();
    
    string element = caster->query_prop("_kato_prop");

    if (objectp(caster))
    {
    	if (caster == target)
    	{
	        caster->catch_tell("You complete your prayer to Psuchae and "
	            + "sense that your request has been heard. An array of "
	            + "shadows appear in your hands and expand to surround you "
	            + "completely. You feel less resistant to "+element+".\n");
	        caster->add_prop("_live_i_cast_kato",1);
	        tell_room(environment(caster), QCTNAME(caster) + " is surrounded "
	            + "by an array of shadows.\n", ({ caster }));
	    }
	    else
	    {
	    	caster->catch_tell("You complete your prayer to Psuchae and "
	            + "sense that your request has been heard. An array of "
	            + "shadows appear in your hands, float over and expand to "+
	            "surround "
	            + target->query_art_name(caster) + " completely. They are now "+
	            "less resistant "+
	            "to "+element+".\n");
	        caster->add_prop("_live_i_cast_kato",1);
	        target->catch_tell(caster->query_The_name(target) + " is "+
	            "surrounded " +
	            "by an array of shadows. They float over and expand to "+
	            "surround you completely. You feel less resistant to "+
	            element+".\n");
	        tell_room(environment(caster), QCTNAME(caster) + " is surrounded "
	            + "by an array of shadows. They float over and expand to "
	            + "surround "+QNAME(target) + " completely.\n",
	            ({ caster, target }));
	    }
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
	object caster = spell_object->query_effect_caster();
    object target = spell_object->query_effect_target();
    
    string element = caster->query_prop("_kato_prop");

    if (objectp(target))
    {
        target->catch_tell("The array of shadows that surrounds you disappears "+
            "and "+
            "in doing so, you sense that the magical vulnerability to "+element+
            " you received has also faded away.\n");
        
    }
    if (objectp(caster))
    {
    	caster->catch_tell("The gift of kato has expired on "+
    	    target->query_art_name(caster)+".\n");
    } 
    caster->remove_prop("_kato_prop");
    caster->remove_prop("_live_i_cast_kato");
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense that the magical vulnerability you "+
            "received is beginning faded away.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the gift of kato.\n");
        caster->remove_prop("_live_i_cast_kato");
    }    
}



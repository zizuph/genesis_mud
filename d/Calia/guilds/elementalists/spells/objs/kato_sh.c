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

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "propchange_base_sh";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// The reduced CAID is the caid left in schirmo, unteresti,dynami and evimero
// if the boosted aspida is active. Elefrinisi can't be cast if aspida boosted.

#define REDUCED_CAID      (REDUCED_BASE_AID * 4.0)
#define MAX_CAID          (BASE_KATO_AID + ELEFRINISI_AID + \
 SCHIRMO_AID + UNTERISTI_AID + DYNAMI_AID + EVIMERO_AID - REDUCED_CAID)

#define DEBUG(x)  find_player("arman")->catch_msg("[ec_kato_sh] " + x + "\n")

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

public float
query_dynamic_kato_resistance(object caster)
{
    float result; 
    int penalty = caster->query_prop(CONDUIT_PENALTY);

    // modify base caid by active maintained spells.
    float total_combat_aid = MAX_CAID;
    float available_combat_aid = BASE_ASPIDA_AID;

    if (!caster_is_maintaining_elefrinisi_effects(caster)) 
    {
        // DEBUG("Elefrinisi aid added.\n");
        available_combat_aid += ELEFRINISI_AID;
    }

    if (!caster_is_maintaining_unteristi_effects(caster)) 
    {
        // DEBUG("unteristi aid added.\n");
        available_combat_aid += UNTERISTI_AID;

        // Unteristi et al have a minimum value
        // which needs to be taken into account if
        // activated after this spell is cast.
        available_combat_aid -= REDUCED_BASE_AID;
    }

    if (!caster_is_maintaining_dynami_effects(caster) &&
        !caster_is_maintaining_thalamos_effects(caster)) 
    {
        // DEBUG("dynami aid added.\n");
        available_combat_aid += DYNAMI_AID;
        available_combat_aid -= REDUCED_BASE_AID;
    }

    if (!caster_is_maintaining_evimero_effects(caster) &&
        !caster_is_maintaining_thalamos_effects(caster)) 
    {
        // DEBUG("evimero aid added.\n");
        available_combat_aid += EVIMERO_AID;
        available_combat_aid -= REDUCED_BASE_AID;
    }

    if (!caster_is_maintaining_schirmo_effects(caster) &&
        !caster_is_maintaining_thalamos_effects(caster)) 
    {
        // DEBUG("schirmo aid added.\n");
        available_combat_aid += SCHIRMO_AID;
        available_combat_aid -= REDUCED_BASE_AID;
    }

    result = (available_combat_aid / total_combat_aid) * 100.0;
    
    switch(penalty)
    {
    	case 3:
    		result = result * 0.5;
    		break;
    	default:
    		result = result * 1.0;
    		break;
    }
    
    return result;
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

    float resist_mod = MAX_CAID * query_dynamic_kato_resistance(ec_caster) / 100.0;
    // DEBUG("Kato resist_mod: " +ftoi(resist_mod));    

    magic_vulnerability = -(ftoi(resist_mod));
    // DEBUG("Kato magic_vulnerability: " +magic_vulnerability);


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
    
    if (result)
    {
        if (intp(result))
        {
            int current_vulnerability = min(100 - result, 100);
            // Magic vulnerability is negative, hence we subtract it.
            current_vulnerability -= magic_vulnerability
                * current_vulnerability / 100;
            return 100 - current_vulnerability;
            
        }
        // This is an unexpected value - it should be an int.  So we
        // will return the unusual type.
        return result;
    }
    
    return magic_vulnerability;
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



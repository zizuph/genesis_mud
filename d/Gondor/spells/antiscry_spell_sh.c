/*
 * /d/Gondor/spells/antiscry_spell_sh.c
 * 
 * Sent to Gondor by Arman in 2020 - this spell is used
 * by one of the lesser rings. Varian - March, 2020
 *
 * Support Shadow for the Divination Protection Spell
 *
 * This shadow gets cloned by the shadow object when the spell
 * is cast. We use this shadow to override the props in a shadow
 * instead of altering it. Using a shadow is typically safer
 * because it can handle stacking from multiple effects well.
 *
 * Created by Petros, modified by Arman - 2017
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>

#ifndef LIVE_I_NO_SCRY
#define LIVE_I_NO_SCRY   ("_live_m_no_scry")
#endif

inherit "/d/Genesis/specials/std/spells/obj/propchange_base_sh";

int spell_power;
object spell_target;

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_name("_goldring_protect_divination_object_");
    spell_object->set_spell_effect_desc("scry ward");
    spell_object->set_short("divination protection spell object");

    spell_power = spell_object->query_spell_effect_power();
    spell_target = spell_object->query_effect_target();

    // 5 minute duration.
    int duration = 300;
    spell_object->set_dispel_time(duration);
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

    string fail_message;

    int scry_prot = min(85, (spell_power / 4));
    int scry_chance = random(100);

    if(scry_prot > scry_chance)
      fail_message = "Your attempt to scry is blocked by powerful divination " +
         "wards.";

    // DEBUG("Scry ward: scry_prot " +scry_prot+ ", scry_chance " +scry_chance+ ".");

    if (prop != LIVE_I_NO_SCRY)
    {
        return result;
    }
    
    if (intp(result))
    {
      if(!fail_message)
      {
        shadow_who->catch_tell("You feel like you are being watched!\n");
        return 0;
      }
        shadow_who->catch_tell("You feel like someone is searching for you, " +
            "but the wards from the simple golden ring protects you.\n");
        return fail_message;
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
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        // target->catch_tell("You feel yourself protected from scrying.\n");
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
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel your simple golden ring's wards disappear.\n");
    }

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
        target->catch_tell("You feel your simple golden ring's wards begin to "
            + "fade.\n");
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
        //caster->catch_tell("You are mentally unable to maintain "
        //    + "the divination protection spell.\n");
    }    
}

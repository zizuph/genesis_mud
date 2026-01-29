/*
 * Support shadow for the mirror portal cantrip
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "../defs.h"
	
#define SOHM_WIND_GUST_PROP ("_sohm_wind_gust_active")

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "propchange_base_sh";

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_spell_effect_desc("wind gust");
    spell_object->set_short("wind gust object");

    int duration = 750 + random(150);
    spell_object->MAX_SPELL_DURATION(MAX_DURATION_CLASS_2, duration);
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

    if (prop != SOHM_WIND_GUST_PROP)
    {
        return result;
    }
    
    if (intp(result))
    {
        return max(1, result + 1);
    }
    else 
    {
        return 1;
    }
}

void 
display_wind_message(object spell_object)
{
    object owner = spell_object->query_effect_target();
    string caster_message, watcher_message;

    switch (random(2))
    {
     case 0:
       caster_message = "A light gust of wind blows around you.\n";
       watcher_message = "A light gust of wind blows around you.\n";
     break;
     case 1:
       caster_message = "An eddy of wind spins frantically in front of you before dissipating.\n";
       watcher_message = "An eddy of wind spins frantically in front of you before dissipating.\n";
     break;
     default:
       caster_message = "A zephyr of wind breezes past you.\n";
       watcher_message = "A zephyr of wind breezes past you.\n";
     break;
    }

    owner->catch_msg(caster_message);
    tell_room(environment(owner), watcher_message, ({ owner }), owner);
   
    set_alarm(75.0, 0.0, &display_wind_message(spell_object));
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{

    set_alarm(10.0, 0.0, &display_wind_message(spell_object));
    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object caster = spell_object->query_effect_target();

    caster->catch_msg("The air around you stills for a moment as your " +
       "gust of wind cantrip ends.\n");

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object caster = spell_object->query_effect_target();

    caster->catch_msg("You feel your gust of wind cantrip is about to end.\n");
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    
}

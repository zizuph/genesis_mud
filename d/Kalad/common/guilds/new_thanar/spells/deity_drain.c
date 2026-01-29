
/*
 * Created by Zignur 2018-01-25
 * A drain spell used by the Thanars in Kalad
 */
 
#pragma strict_types
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/drain";


/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_drain_damage(object caster, object target, mixed *result, int healing)
{
    string how;

    switch (result[3])
    {
        case 0..20:
            how = "barely drained";
            break;
        case 21..50:
            how = "slightly drained";
            break;
        case 51..80:
            how = "somewhat drained";
            break;
        case 81..110:
            how = "rather drained";
            break;
        case 111..140:
            how = "very drained";
            break;
        case 141..170:
            how = "extremely drained";
            break;
        default:
            how = "almost completely drained";
            break;
    }

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + ".\n",
        target, ({ caster, target }));
        
    if (healing)
    {
        caster->catch_msg("You feel the your powers draw life from your "
				+"enemy, healing your wounds.\n");
        caster->tell_watcher(QCTNAME(caster) + " is healed by the his " +
                "dark and glorious power.\n");
        target->catch_msg("You feel your health being siphoned as the Thanar " +
                "draws your life from you.\n");   
    }
} /* desc_drain_damage */

/*
 * Function:    config_drain_spell
 * Description: Config function for the drain spell.
 */
public void
config_drain_spell()
{
    set_spell_name("tdrain");
    set_spell_desc("Call upon your power to drain life from foes");

    set_spell_target(spell_target_one_other_present_living_or_enemy);

    set_spell_task(TASK_HARD);
    set_spell_ingredients(query_drain_ingredients);
    
    set_spell_fail("You've lost concentration.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each drain spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(33.0);
    
    set_drain_percentage(33);
    
} /* config_drain_spell */

/*
 * Function:    query_drain_ingredients
 * Description: This function defines what components are required for
 *              this drain spell.
 */
public string *
query_drain_ingredients(object caster)
{
    return ({ });
} /* query_drain_ingredients */

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1.  object    The caster
 *                2.  mixed *   The targets
 *                3.  string    The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    caster_message = "You close your eyes and draw on the power within " +
          "you granted by the power of those who praise you.\n";
    watcher_message = QCTNAME(caster) + " closes "+ 
          caster->query_possessive()+  " eyes drawing upon the power granted "
          +"by the prayers offered up to him by the humans who praise him.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }));  
    
    setuid();
    seteuid(getuid());  
} /* concentrate_msg */

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;
    
    target = targets[0];
    caster_message = "Your hands are surrounded by a dark swirling mist. "
			+"You reach out towards " + QTNAME(target) + " grinning evilly "
			+"as your Dark Touch reaches " + target->query_objective()+ ".\n";
            
    target_message = QCTNAME(caster)+ " hands are surrounded by "+
            "a dark swirling mist, " + caster->query_pronoun() + " "  +
            "grins evilly as "+ caster->query_pronoun() + " reach out " +
            "towards you with " + caster->query_possessive() + 
            " Dark Touch.\n";
            
    watcher_message = QCTNAME(caster)+ " hands are surrounded by "+
            " a dark swirling mist, " + caster->query_pronoun() + " "  +
            "grins evilly as "+ caster->query_pronoun() + " reach out "   +
            "towards " + QTNAME(target) + " with " +
            caster->query_possessive() + " Dark Touch.\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
} /* desc_harm_cast */

    
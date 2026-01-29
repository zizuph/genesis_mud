/*
 * Created by Zignur 2018-01-25
 * A damage spell used by Thanar in Kalad
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_spell_name("tdamage");
    set_spell_desc("Call your powers to harm your foes.");
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(75.0);
    set_spell_task(TASK_HARD); 

    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);

} /* config_harm_spell */

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    // no regents required
    return ({ "" });
}  /* query_harm_ingredients */


/*
 * Function:    query_spell_can_be_learned
 * Description: See if the user can learn/use the spell
 * Arguments:   object player
 * Returns:     1 Success 0 Fail
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // Npcs can always learn the spell.
        return 1;
    }
    
    return 1;
} /* query_spell_can_be_learned */

/*
 * Function:    check_valid_action
 * Description: check if the spell can be used.
 * Arguments:   object caster, mixed * targets, string arg, int execute
 * Returns:     1 Success 0 Fail
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    if(caster->query_skill(SS_SPELLCRAFT) < 50)
    {
       caster->catch_tell("You lack the needed skills to use this prayer.\n");
       return 0;
    }
  
    return 1;
} /* check_valid_action */

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
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
 
    string how;

    switch (result[3])
    {
        case 0..20:
            how = "barely hurt";
            break;
        case 21..50:
            how = "slightly hurt";
            break;
        case 51..80:
            how = "somewhat hurt";
            break;
        case 81..110:
            how = "rather hurt";
            break;
        case 111..140:
            how = "hurt";
            break;
        case 141..170:
            how = "very hurt";
            break;
        default:
            how = "extremely hurt";
            break;
    }

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + ".\n",
        target, ({ caster, target }));

} /* desc_harm_damage */

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

    caster_message = "You raise your hands and a gigantic black snake "
			+"materializes out of the shadows, sinking its deadly fangs into " 
			+ QTNAME(target) + " injecting venom into the wound.\n";
            
            
    target_message = QCTNAME(caster)+ " raises his hands and a gigantic "+
            "black snake materializes from the shadows, sinking its deadly " +
            "fangs into you, injecting venom into the wound.\n";

    watcher_message = QCTNAME(caster)+ " raises his hands and a gigantic " +
            "black snake materializes from the shadows, sinking its deadly " + 
            "fangs into " + QTNAME(target) + " injecting venom into the wound.\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
} /* desc_harm_cast */

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
   
} /* resolve_harm_spell */

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need a regent.\n");
} /* hook_no_ingredients_fail */

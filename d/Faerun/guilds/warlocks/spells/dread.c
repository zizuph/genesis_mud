/*
 * Fear spell for the Warlocks of Faerun
 *
 * Shamelessly borrowed from OotS, by Arman
 *
 * Nerull 2018
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/unfinished/turn_target";

/*
 * Function name:   turn_target_success
 * Description:     Calculate the success of the turn target.
 * Arguments:       (object) spell_object - the spell object in question
 * Returns:         (int) - The success of the spell effect
 */
public int
turn_target_success(object spell_object)
{
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    int success = caster->resolve_task(
    TASK_ROUTINE,   ({  SKILL_WEIGHT, 40, TS_INT, SKILL_WEIGHT, 40, TS_WIS,
                        SKILL_WEIGHT, 20, SKILL_AVG, SS_ELEMENT_WATER,
                        SS_SPELLCRAFT, SKILL_END }),
    target,         ({  SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 60, TS_DIS,
                        SKILL_WEIGHT, 20, SKILL_AVG, SS_ELEMENT_WATER,
                        100, SKILL_END}));
    
    return success;
} /* turn_target_success */


/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object  target = spell_object->query_spell_effect_target(),
            caster = spell_object->query_spell_effect_caster();
    
    if (objectp(caster) && objectp(target))
    {
        target->catch_tell("Your fear of " + caster->query_the_name(target)
        + " fades.\n");
        
        caster->catch_tell("You sense that the spook effect " +
          "on " + target->query_the_name(caster) + " has faded.\n");
    }
} /* hook_spell_effect_ended */


public object *
target_one_present_living(object actor, string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        actor->catch_tell("Cast on who?\n");
        
        return ({ actor });
    }
    
    parse_command(str, ({}), "[at] / [on] [the] %s", str);
    oblist = PARSE_THIS(str, "%l");
    
    if (!sizeof(oblist))
    {
        if ((str == "me") || (str == "myself") || 
            (str == actor->query_real_name()))
        {
            actor->catch_tell("You can't cast this spell on yourself!\n");
            
            return ({ actor });
        }

        actor->catch_tell("There is no " + str + " here.\n");
        return ({});
    }
    
    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
        "select one target.\n");
        return ({});
    }
    
    if (oblist[0]->query_prop(NPC_I_NO_RUN_AWAY))
    {
        actor->catch_tell("Your target is immune to this spell.\n");
        
        return ({});
    }
        
    string race = oblist[0]->query_race();
        
    if (race == "hobbit" || race == "gnome" || race == "kender")
    {
        return oblist;
    }
        
    actor->catch_tell("You can only cast this spell on "
    +"hobbits and gnomes.\n");
        
    return ({});
}


/*
 * Function:    config_turn_target_spell
 * Description: Config function for turn_target spells. Redefine this in your
 *              own turn_target spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_turn_target_spell()
{
    set_spell_name("urgashe");
    set_spell_desc(" - Spook: Cause hobbits and gnomes to flee");
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
        
    set_locate_limit(3);
    set_turn_target_visual(0);
    
    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_ILLUSION, 40);
    
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients(query_turn_target_ingredients);
    set_spell_target(target_one_present_living);
}


/*
* Function:    query_spell_can_be_learned
* Description: Place restrictions on whether this spell can be used
*              by the guild member.
*/
public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return 1;
    }
    
    // If we are testing spells regardless of rank and selection.
    if (SPELLTESTING == 1)
    {
        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()) == 3)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= FEAR_UNLOCK)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    return 1;
                }
           }
       }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()) == 3)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= FEAR_UNLOCK)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    return 1;
                }
           }
       }
    }
    
    return 0;
}


/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    return 1;
}


public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has already been spooked!\n");
    }
}


/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing
specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your spell.\n");
}


// HOOKS TO BE DEFINED

/*
* Function name: concentrate_msg
* Description:   Give messages indicating that spell concentration has begun
* Arguments:     1. (object)   The caster
*                2. (mixed *) The targets
*                3. (string)   The arguments passed to the "cast" command
*/
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;

    caster_message = "As you surreptitiously whisper the long "
    +"forgotten words, the sounds reverberates in increasing "
    +"intensity, only to fade as you draw arcane powers from the "
    +"shadows!\n";
    
    watcher_message = "A chorus of eerie whispers permeate the area in "
    +"increasing intensity, only to fade again as "+QCTNAME(caster)
    +" turns inwards.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function:    query_turn_target_ingredients
 * Description: This function defines what components are required for
 *              this turn_target spell.
 */
public string *
query_turn_target_ingredients(object caster)
{
    // If we are testing spells, no components
    if (SPELLTESTING_NOCOMPS == 1)
    {
        return ({ });
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return ({ });
    }
    
    return ({  "_dread_charge" });
}


/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You are not properly prepared for the Urgashe spell!\n");
}


/*
 * Function name:   resolve_turn_target_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_turn_target_spell(object caster, object *targets, int *resist, int result,
                     mapping paths)
{
    caster->catch_msg(COMPOSITE_LIVE(targets) + " suddenly screams and "
    +"jerks away from you, desperately looking for an exit!\n");
    
    targets->catch_msg("You scream and jerks away as you meet " 
    +QTPNAME(caster) +"'s ominous gaze. You feel your heart racing and you "
    +"desperately looks for an exit!\n");
    
    tell_room(environment(caster), COMPOSITE_LIVE(targets) +" suddenly "
    +"screams and jerks away from "+QTPNAME(caster) +", desperately looking "
    +"for an exit!\n",
    ({ caster }) + targets, caster); 
} /* resolve_locate_spell */





















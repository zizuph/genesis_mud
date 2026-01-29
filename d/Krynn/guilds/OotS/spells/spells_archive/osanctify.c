/*
 * sanctify spell... allows for the creation of the holy water spell component.
 */
 
#pragma strict_types

#include "../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

#include <macros.h>
#include <tasks.h>

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "../oots_god_descs.h"

// Prototypes
public void resolve_sanctify_spell(object caster, mixed * targets, int * resist, int result);
 
/*
 * Function:    config_sanctify_spell
 * Description: Config function for sanctify spells. Redefine this in your
 *              own sanctify spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_sanctify_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
}

/*
 * Function:    query_sanctify_ingredients
 * Description: This function defines what components are required for
 *              this sanctify spell.
 */
public string *
query_sanctify_ingredients(object caster)
{
    return ({ "water","vial","silver coin" });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "silver coin, water, vial";
}

private nomask void
config_required_parameters()
{
    set_spell_stationary(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("osanctify");
    set_spell_desc("Sanctify - purify water making it holy");

    set_spell_mana(15); // cosmetic spell, half mana cost
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_sanctify_ingredients);

    set_spell_fail("Your prayer fails.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_sanctify_spell();
    
    // Call this after the config_sanctify_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
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
        // npcs can always learn the spell.
        return 1;
    }

    // Level 1 spell
    if(OOTS_LEVEL(player) < 1)
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }  

    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not " +
           "align with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    } 
    
    return result;    
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_sanctify_spell(caster, targets, resist, result);

    setuid();
    seteuid(getuid());
    // Perform the actual creation of holy water   
    object water = clone_object(OOTS_OBJS + "holywater");
    water->move(environment(caster));

}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_sanctify_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_sanctify_spell(object caster, mixed * targets, int * resist, int result)
{

}

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
    object target = targets[0];

        caster_message = "You lower yourself to your knees and close " +
            "your eyes, offering a prayer to " +oots_god_name(caster)+ 
            ".\n";
        watcher_message = QCTNAME(caster) + " lowers " +HIM(caster)+ 
             "self to " +HIS(caster)+ " knees and closes "+ HIS(caster)+ 
             " eyes, offering a prayer to the " +oots_god_desc(caster)+ 
             " " +oots_god_name(caster)+".\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

void
hook_use_ingredients(object *ingrs)
{
    int i, j, k; // coin, vial, water
    string *arr;
     
    if (IS_COINS_OBJECT(ingrs[0]))
    {       
       i = 0;
       if(ingrs[1]->query_prop("_heap_s_unique_id") == "_std_potion_vial")
       {
         j = 1;
         k = 2;
       }
       else
       {
         j = 2;
         k = 1;
       }
    }
    else if(ingrs[0]->query_prop("_heap_s_unique_id") == "_std_potion_vial")
    {       
       j = 0;
       if(IS_COINS_OBJECT(ingrs[1]))
       {
         i = 1;
         k = 2;
       }
       else
       {
         i = 2;
         k = 1;
       }
    }
    else
    {
       k = 0;
       if(IS_COINS_OBJECT(ingrs[1]))
       {
         i = 1;
         j = 2;
       }
       else
       {
         i = 2;
         j = 1;
       }
    }

    write("You pour " +LANG_ASHORT(ingrs[k])+ " into " +
          LANG_ASHORT(ingrs[j]) + " while gently rubbing " +
          LANG_ASHORT(ingrs[i]) + " with your thumb. As you " +
          "whisper "+oots_god_name(TP)+ "'s name " +
          LANG_THESHORT(ingrs[i])+ " begins to evanesce, sanctifying "+
          LANG_THESHORT(ingrs[k])+ ", leaving a phial of holy water " +
          "before you.\n");
    say(QCTNAME(TP)+ " pours " +LANG_ASHORT(ingrs[k])+ " into " +
          LANG_ASHORT(ingrs[j])+ " while gently rubbing " +
          LANG_ASHORT(ingrs[i]) + " with " +HIS(TP)+ " thumb. "+
          C(HE(TP))+ " whispers "+oots_god_name(TP)+ "'s name and " +
          LANG_THESHORT(ingrs[i])+ " begins to evanesce, sanctifying "+
          LANG_THESHORT(ingrs[k])+ ".\n");
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
    string ing = "";
    int size = 0;

    foreach(string ingredient: ingredients_needed)
    {
       string ingr = ingredient;
       size++;
       ing += ingr;

       if (sizeof(ingredients_needed) - size == 1)
             ing += " and ";
       else if (sizeof(ingredients_needed) - size > 1)
               ing += ", ";
     }

    write("Your sanctify prayer requires a " +ing+ " to create a " +
          "phial of holy water.\n");
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id("oots_guild_object"))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        if (random(10))
            return 0;
    }
        
    return ret;
}

/*
 * Rejuvenation - Heal yourself
 * Zizuph July 2022
 */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../rangers.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "heal";
inherit VIRTUE_SPELL_INHERIT;

#define LOTHORE_KEEP_PERCENTAGE (83)

/*
* Function:    config_heal_spell
* Description: Config function for heal spells. Redefine this in your
*              own heal spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_heal_spell()
{
    set_spell_name("heal");
    set_spell_desc("Heal someone's wounds.");

    set_spell_optional_ingredients(({ "lothore" }));
    set_spell_ingredients(({ }));

    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_ability_stats(STAT_WEIGHTING);

    // 1.8 for a slightly bigger heal.
    set_spell_time_factor(1.8);

    // Can be componentless, and one herb per six casts.
    set_spell_component_factor(COMPONENT_AID_LOW);
    
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    mixed ingredients = query_ability_found_components(this_player());

    if (sizeof(ingredients))
      return 100.0;
  
    return 50.0;
}

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
    int known_spells = player->query_skill(SS_RANGER_SPELL_LIST);
    if (!(known_spells & SPELL_HEAL))
    {
        return 0;
    }
    if (player->query_ranger_has_virtues())
    {
        return has_spellcasting_virtue(player);
    }
    return 1;
}

public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        write("The gifts of Este are for healing, not harm.\n");
        return 0;
    }
    
    return 1;
}


/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({ });
}

/*
* Function:    resolve_heal_spell
* Description: Called at the beginning of resolve_spell in order to perform
*              spell specific actions.
* Arguments:   Same as resolve_spell
*/
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}


/*
* Function name: hook_describe_heal_cast
* Description:   Describe casting of the spell. This takes place before the
*                actual healing happens.
*                This can be redefined for custom messages.
* Arguments:     object caster   - the caster
*                object * target - the target(s)
*/
public void
hook_describe_heal_cast(object caster, object *targets)
{
    string msg;
    mixed ingredients = query_ability_found_components(caster);

    if (sizeof(ingredients))
        msg = "use the virtues of the red heart-shaped flower";
    else
        msg = "call upon Este, the Valie of Healers,";

    if (targets[0] != caster)
    {
        caster->catch_tell("You " + msg + " in a attempt to " +
            "heal some of " + targets[0]->query_the_possessive_name(caster) +
            " wounds.\n");

        targets[0]->catch_msg(QCTNAME(caster) +
            " presses " + caster->query_possessive(targets[0]) + 
            " hand to your forehead and murmurs a soft chant in an ancient " +
            "tongue.\n");
    }
    else
    {
        caster->catch_tell("You " + msg + " in an attempt to heal " +
            "yourself.\n");
    }
}


/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    if (heal_amounts[0] <= 0 || (targets[0]->query_hp() == targets[0]->query_max_hp()))
    {
        targets[0]->catch_tell("You feel a slight tingle, but " +
            "nothing more.\n");
        if (caster != targets[0])
            caster->catch_tell("You feel that your prayer had no effect.\n");
    }
    else
    {
        adjust_valar_disfavour(caster, targets[0], 1.5);

        caster->catch_tell("You feel someone answering your prayer.\n");
        targets[0]->catch_tell("Strange energies flow through your " +
            "wounds, and you feel healthier!\n");
    }

}

public void
consume_components(object *ingrs)
{
    foreach (object ingredient : ingrs)
    {
        if (ingredient->query_prop("_savable_from_consumption"))
        {
            this_object()->restore_components(({ ingredient }));
        }
        else
        {
            ingredient->remove_object();
        }
    }
} /* consume_components */


/*
 * Function name: hook_use_ingredients
 * Description:   This function should return the message that will be printed
 *                to the caster when he/she has used some ingredients.
 * Arguments:     ingrs - The ingredients that will be used.
 * Returns:       The message to print.
 */
public void
hook_use_ingredients(object *ingrs)
{
    object * consumed = ({ });
    foreach(object ob : ingrs) 
    {
        if (random(100) < LOTHORE_KEEP_PERCENTAGE)
        {
            write("Luckily, you manage to keep all ingredients intact.\n");
            ob->add_prop("_savable_from_consumption", 1);
        }
        else
        {
            consumed += ({ ob });
        }
    }

    consumed = filter(consumed, &->check_seen(this_player()));
    desc_use_ingredients(consumed);
}

/*
* Function name: hook_describe_harm_result
* Description:   Describe the results of the spell upon its targets. This
*                happens after the healing has happened.
*                This can be redefined for custom messages.
* Arguments:     object caster   - the caster
*                object * target - the target(s)
*                int * harm_amounts - the amounts healed
*/
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    // This should not happen, as the spell does not affect the undead.
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
    // All ingredients are optional.
}





/*
 * phammer enchantment for Priests of Takhisis
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <wa_types.h>
#include <files.h>
#include <language.h>
#include "/d/Ansalon/common/defs.h"

#include "../guild.h"
#include "../spells.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "shadow";
inherit GUILDDIRSPELL + "common";

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 4;
}

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{
    set_spell_name("phammer");
    set_spell_desc("Bless a bludgeon weapon");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR,  20);
    set_spell_form(SS_FORM_ENCHANTMENT, 20);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_combat_aid(40.0);

    set_spell_target(spell_target_one_present_non_living_or_wielded_weapon);
   
    set_shadow_filename(GUILDDIRSPELL + "obj/phammer_sh");
}

/*
 * Function:    is_valid_weapon_for_spell
 * Description: This returns whether this particular weapon is valid to
 *              be shadowed. This should be masked to match
 *              what type of weapons are valid to use for shadowing.
 *
 * Arguments: object obj - the object to check for validity.
 * Returns: integer, 0 for invalid, 1 for valid.
 */
public int
is_valid_weapon_for_spell(object weapon)
{
    if (!objectp(weapon))
    {
        return 0;
    }

    if(weapon->query_wt() != W_CLUB)
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
}

object
holy_water_ingr(object *possible, object *found)
{
    object *list;
    int i;
    
    list = possible - found;
    for (i = 0 ; i < sizeof(list) ; i++)
    {
        if (list[i]->query_is_takhisis_unholy_water())
            return list[i];
        if (member_array("holy water", list[i]->query_names()) >= 0)
            return list[i];
    }

    return 0;
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{
    return ({holy_water_ingr,"tuo"});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (!IS_WEAPON_OBJECT(targets[0]))
    {
        caster->catch_tell("You can only cast this spell on clubs.\n");
        return 0;
    }
  
    if (!is_valid_weapon_for_spell(targets[0]))
    {
        caster->catch_tell("You can only cast this blessing on clubs.\n");
        return 0;
    }
    
    if (!targets[0]->query_wielded())
    {
        object weapon = targets[0];

        caster->catch_tell("Your " + weapon->short() + " must be wielded for the blessing.\n");
	return 0;
    }

    if(caster->query_prop(ACTIVE_ENCHANTMENT))
    {
        caster->catch_tell("You can only maintain one blessed weapon at a time.\n");
        return 0;
    }

    if(caster->query_prop(DARK_LADY_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Lady, you cannot " +
           "request this martial blessing.\n");
        return 0;
    }
  
    return 1;
}

public void
hook_use_ingredients(object *ingrs)
{
    int i;

    if (ingrs[0]->query_is_takhisis_holy_water())
        i = 0;
    else
        i = 1;

    write("The contents of the " + LANG_THESHORT(ingrs[i]) +
          " starts boiling and vaporises along with the phial " +
          "and " + LANG_THESHORT(ingrs[!i]) + " which decomposes " +
          "in the steam.\n");
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id(MEDALLION_ID))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name:   query_ability_hit
 * Description:     Returns the set ability to-hit value.
 * Arguments:       (object) actor
 *                  (mixed) target
 *                  (object *) items
 * Returns:         (int) ability hit value
 */
public int
query_ability_hit(object actor, mixed target, object * items)
{
    if (calling_function() == "query_spell_tohit")
    {
        // harder to cast on when in poor standings
        if (actor->query_skill(PS_STANDING) < -900)
            return convert_task_to_hit(TASK_FORMIDABLE);
    
        if (actor->query_skill(PS_STANDING) < -300) 
            return convert_task_to_hit(TASK_HARD);
    }
    
    return ::query_ability_hit(actor, target, items);
} /* query_ability_hit */

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed *
check_required_items(object actor, mixed * targets,string arg, int pretest)
{
    return filter(actor->query_clothing(-1), &is_valid_medallion(actor,));
}

/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}

/*
 * Function name:   query_ability_item_modifier
 * Description:     
 * Arguments:       1. (object) actor
 *                  2. (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public int
query_ability_item_modifier(object caster, mixed *items)
{
    items = filter(items, &is_valid_medallion(caster,));
    
    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!sizeof(items))
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    
    return 100;
} /* query_ability_item_modifier */
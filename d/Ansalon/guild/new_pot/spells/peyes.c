/*
 * pEyes
 */
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "darkvision";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit GUILDDIRSPELL + "common";

#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 5;
}

/*
 * Function:    config_darkvision_spell
 * Description: Config function for darkvision spells. Redefine this in your
 *              own darkvision spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_darkvision_spell(void)
{
    set_spell_name("peyes");
    set_spell_desc("Give yourself the vision of a dragon");

    set_spell_element(SS_ELEMENT_LIFE,  45);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("Your prayer is unheard.\n");

    // Can cast peyes on others if in Aspect of the Lady
    set_spell_target(spell_target_one_present_living);

    // Set the effect object filename
    set_spell_object(EYES_OBJ);
}

/*
 * Function:    query_darkvision_ingredients
 * Description: This function defines what components are required for
 *              this dark vision spell.
 */
public string *
query_darkvision_ingredients(object caster)
{
    return ({ "_leftover_eye_powder", "_leftover_eye_powder"});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if(!caster->query_prop(DARK_LADY_ASPECT) && (targets[0] != caster))
    {
        caster->catch_tell("You can only cast this prayer on others when " +
            "under the aspect of the Dark Lady.\n");
        return 0;
    }

    return 1;
}

public void
hook_use_ingredients(object *ingrs)
{
    string *arr = ingrs->query_race();

    if (arr[0] == arr[1])
        arr = arr[1..];

    write("The pair of " + COMPOSITE_WORDS(arr) + " eyes " +
        "glow briefly, their pupils changing to reptilian, before " +
        "they are consumed.\n");
}

/*
 * Function:    resolve_darkvision_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_darkvision_spell(object caster, mixed * targets, int * resist, int result)
{
    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
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

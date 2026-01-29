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

inherit "/d/Genesis/specials/std/spells/shadow";
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
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_target(spell_target_one_present_non_living);
   
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

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);
  
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
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}
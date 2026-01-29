/*
 * pBless
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/stoneskin";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>

inherit GUILDDIRSPELL + "common";

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 6;
}

/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_stoneskin_spell()
{
    set_spell_name("pbless");
    set_spell_desc("Invoke the Dark Queen's blessing");

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE,  60);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);

    // When in aspect of the Dark Lady, combat aid is set to 60.
    set_spell_combat_aid(40.0);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // Can only cast pbless on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(GUILDDIRSPELL + "obj/pbless");

}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    return ({ "onoclea" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if(BETA_CAID_MOD)
        set_spell_combat_aid(36.0);

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    if(caster->query_prop(DARK_LADY_ASPECT))
    {
      if(BETA_CAID_MOD)
        set_spell_combat_aid(54.0);
      else
        set_spell_combat_aid(60.0);
    }

    int c_aid = ftoi(query_spell_combat_aid());
    // DEBUG("Pbless aid: " + c_aid);

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already blessed by Takhisis, and " +
    	    "the prayer has no effect.\n");
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
    write("You need an onoclea herb to invoke the blessings of the Dark Queen!\n");
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
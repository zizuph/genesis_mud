/*
 * pSlow
 */
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "slow";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"

inherit GUILDDIRSPELL + "common";

#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()


/*
 * Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 10;
}

/*
 * Function:    config_slow_spell
 * Description: Config function for slow spells. Redefine this in your
 *              own slow spells to override the defaults.
 */
public void
config_slow_spell(void)
{
    set_spell_name("pslow");
    set_spell_desc("Slow down the movement of your enemy");

    set_spell_element(SS_ELEMENT_AIR, 35);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_fail("Your prayer is unheard.\n");

    set_spell_object(GUILDDIRSPELL + "obj/pslow");

    // By default, set the slow interval to 2.5
    set_slow_interval(2.5);
}

/*
 * Function:    query_slow_ingredients
 * Description: This function defines what components are required for
 *              this slow spell.
 */
public string *
query_slow_ingredients(object caster)
{
    return ({ "tiger lily" });
}

public int
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
	return 0;

    if (!present("needle", caster) &&
	!caster->query_prop("_wizard_ignore_spell_ingredients"))
    {
        caster->catch_tell("You need a needle to complete this prayer!\n");
        return 0;
    }

    return 1;
}

/*
 * Function:    resolve_slow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_slow_spell(object caster, mixed *targets, int * resist, int result)
{
    if (!present("needle", caster) &&
	!caster->query_prop("_wizard_ignore_spell_ingredients"))
    {
    	caster->catch_tell("In a hurry you cannot find a needle!\n");
    }
    
    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
}

/*
 * Function:    hook_describe_cast_slow
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_slow(object caster, object *targets)
{
    object tar = targets[0];

    caster->catch_msg("You prick your thumb with a needle and blow "+
	"a drop of blood in "+ QTPNAME(tar) +" direction. The air around " +
	HIM(tar) + " blooms in to a red haze.\n");

    tar->catch_tell(caster->query_The_name(tar) +" pricks "+ HIS(caster) +
	" thumb with a needle and blows a drop of blood in your "+
	"direction. The air around you blooms in to a red haze.\n");

    tell_room(environment(caster), QCTNAME(caster) +" pricks "+
	HIS(caster) +" thumb with a needle and blows a drop of blood in "+
	QTPNAME(tar)+" direction. The air around "+ HIM(tar) +
	" blooms in to a red haze.\n", ({ caster, tar }), caster);
}

/*
 * Function:    hook_slow_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_slow_resisted(object caster, object * targets)
{
    object tar = targets[0];

    caster->catch_msg("You sense that " + QTNAME(tar) + " is " +
	"not affected by your unholy prayer.\n");
    tar->catch_msg("You shrug off " + QTPNAME(caster) +
	" unholy prayer to slow you down.\n");
    caster->tell_watcher(QCTPNAME(caster) + " unholy prayer doesn't "+
	    "seem to succeed in slowing " + COMPOSITE_LIVE(tar) + ".\n",
        ({ caster, tar }));
}

public void
hook_use_ingredients(object *ingrs)
{
   write(LANG_THESHORT(ingrs[0]) + " shimmers briefly into " +
         "a myriad of colours before crumbling to dust and " +
         "blowing away.\n");
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
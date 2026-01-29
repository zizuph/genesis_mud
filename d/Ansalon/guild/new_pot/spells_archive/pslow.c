/*
 * pSlow
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/slow";

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
    set_spell_task(TASK_ROUTINE);

    set_spell_stationary(0);
    set_spell_offensive(1);
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

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300)
	set_spell_task(TASK_HARD);

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

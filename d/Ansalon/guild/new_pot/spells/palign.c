/*
 * pAlign
 */
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "alignment";

#include "../guild.h"
#include "../spells.h"
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include <tasks.h>

inherit GUILDDIRSPELL + "common";

#include <ss_types.h>
#include <macros.h>


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 2;
}

/*
 * Function:    config_alignment_spell
 * Description: Config function for alignment spells. Redefine this in your
 *              own alignment spells to override the defaults.
 */
public void
config_alignment_spell(void)
{
    set_spell_name("palign");
    set_spell_desc("Detect someone's alignment");

    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_fail("Your prayer is unheard.\n");

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_1);
    set_spell_task(TASK_EASY);

}

/*
 * Function:    query_alignment_ingredients
 * Description: This function defines what components are required for
 *              this alignment spell.
 */
public string *
query_alignment_ingredients(object caster)
{
    return ({  });
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed *targets, string arg)
{
    caster->catch_tell("You surreptitiously touch your black medallion "+
	"and whisper a prayer to the Queen of Darkness.\n");
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell,
 *                                     who to check the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{
    int num, a = 1;
    string s;

    if (!objectp(target) || environment(caster) != environment(target))
    {
        caster->catch_tell("There is noone to focus your sight on.\n");
        return;
    }

    sscanf(OB_NUM(target), "%d", num);

    a += (100 - caster->query_skill(SS_APPR_MON)) * 4;
    a = random(2 * a, num) - a;
    a += target->query_alignment();

    if (a < -750)
        s = "midnight black";
    else if (a < -400)
        s = "black";
    else if (a < -100)
        s = "dark grey";
    else if (a < 100)
        s = "grey";
    else if (a < 400)
        s = "light grey";
    else if (a < 750)
        s = "white";
    else
        s = "pure white";

    caster->catch_tell("You focus your sight above and beyond " +
	target->query_the_name(caster) + ", and for a short while you can " +
	"faintly detect a " + s + " aura.\n");

    //Milan fixed runtime errors here
    object tp = this_player();
    set_this_player(caster);

    tell_room(environment(caster), QCTNAME(caster) + " seems to look " +
	"intently at something just behind " + QTNAME(target) + ".\n",
	({ caster, target }), caster);

    set_this_player(tp);

    if (caster->check_seen(target))
    {
	target->catch_tell(caster->query_The_name(target) +
	    " seems to look intently at something just behind you.\n");
    }

    if (caster->query_npc())
        caster->cast_palign_hook(s, target);
}

/*
 * Function name : hook_fail_target_not_present
 * Description   : Writes output to caster when the target is not present.
 * Arguments     : object caster - the person casting the alignment spell.
 *               : object target - the specified target of the alignment spell.
 */
public void
hook_fail_target_not_present(object caster, object target)
{
    caster->catch_tell("Your specified target is no longer here.\n");
}


/*
 * Function name: resolve_alignment_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets  - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_alignment_spell(object caster, mixed* targets, int* resist, int result)
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
/*
 * pscourge - Arman 2016
 *
 * At will damage spell for the PoT. This is based
 * on the Genesis generic At-Will Harm spell (Petros 2009).
 */
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "at_will_harm";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"

inherit GUILDDIRSPELL + "common";

#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>

#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()

#define FILTER_CLUBS(x) filter(x->query_weapon(-1), \
    &operator(==)(W_CLUB) @ &->query_wt())

// Defines
#include "pscourge_desc.h"


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 *
public int
query_spell_level(void)
{
    return 2;
}
 */

/*
 * Function:    config_at_will_spell
 * Description: Config function for at will damage spells. Redefine this in your
 *              own at will spells to override the defaults.
 */
public void
config_at_will_spell(void)
{
    set_spell_name("pscourge");
    set_spell_desc("Scourge your enemy with an unholy word of pain");
    set_spell_element(SS_ELEMENT_LIFE, 35);
    set_spell_form(SS_FORM_ENCHANTMENT, 20);

    set_spell_combat_aid(60.0);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);    
}

public int 
check_valid_action(object caster, mixed *targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    int c_aid;
    object *clubs = FILTER_CLUBS(caster);

    if (!sizeof(clubs))
    {
        caster->catch_tell("You need to be wielding a mace or club " +
	    "to scourge your enemies.\n");
        return 0;
    }
    
    return 1;
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
    object *clubs = FILTER_CLUBS(caster);
    string weaps = COMPOSITE_WORDS(clubs->short());

    caster->catch_tell("You ready your " + weaps + " and whisper a prayer "+
	"to the Queen of Darkness.\n");

    tell_room(environment(caster), QCTNAME(caster) + " readies " +
	HIS(caster) + " " + weaps + " and whispers a prayer to the "+
	"Queen of Darkness.\n", ({ caster }), caster);
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their at will spell again.
 */
public void 
hook_special_complete(void)
{
    write("You feel you can once more call on the Queen of Darkness "+
	"to scourge your foes.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown(void)
{
    write("You do not feel you can call on the aid of the Queen of "+
	"Darkness to scourge your foes just yet.\n");
}

public void
hook_already_active(object ability)
{
    write("You are in the process of scourging your foes!\n");
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
{
    pscourge_desc_cast(caster, targets[0]);
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    pscourge_desc_damage(caster, target, result);
}

/*
 * Function:    query_insufficient_skills
 * Description: Returns the skills that are not high enough to cast this
 *              spell.
 */
public int *
query_insufficient_skills(object caster)
{
    int *needed_skills = ({ }),
	*check_skills = ({ SS_ELEMENT_LIFE, SS_FORM_ENCHANTMENT });
    
    foreach (int snum : check_skills)
    {
        // minimum of superior student
        if (caster->query_skill(snum) < 10)
            needed_skills += ({ snum });
    }

    return needed_skills;
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



/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public nomask float
query_spell_combat_aid_modifier()
{
    // for PoT below 1000 PS_STANDING, their pscourge caid ranges
    // from between 40 and 60. Over 1000 defaults to 60.
    float modifier = 100.0;
    float pot_standing = itof(min(1000, this_player()->query_skill(PS_STANDING)));
    
    modifier = max(68.0, modifier * pot_standing / 1000.0);
    
    if(BETA_CAID_MOD)
        modifier = modifier * 9.0 / 10.0;

    return min(100.0, modifier);
}

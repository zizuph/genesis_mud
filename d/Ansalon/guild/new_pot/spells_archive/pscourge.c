/*
 * pscourge - Arman 2016
 *
 * At will damage spell for the PoT. This is based
 * on the Genesis generic At-Will Harm spell (Petros 2009).
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/at_will_harm";

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
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(60.0);
    set_spell_task(TASK_ROUTINE);    
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

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    // for PoT below 1000 PS_STANDING, their pscourge caid ranges
    // from between 40 and 60. Over 1000 defaults to 60.

    if(caster->query_skill(PS_STANDING) > 1000)
        c_aid = 60; 
    else
        c_aid = max(40, (caster->query_skill(PS_STANDING) / 50) + 40);

    if(BETA_CAID_MOD)
        c_aid = (c_aid / 10) * 9;

    set_spell_combat_aid(c_aid);

    // DEBUG("pscourge combat aid: "+c_aid+".");

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

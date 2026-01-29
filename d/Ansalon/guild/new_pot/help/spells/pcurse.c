/*
 * pCurse
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/illfortunate";

#include "../guild.h"
#include "../spells.h"

inherit GUILDDIRSPELL + "common";

#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define ACTIVE_CURSE "_pot_curse_active"
#define BLIND_CURSE "_pot_blind_curse"

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int 
query_spell_level(void)
{
    return 10;
}

/*
 * Function:    config_illfortunate_spell
 * Description: Config function for illfortunate spell. Redefine this in your
 *              own illfortunate spells to override the defaults.
 */
public void
config_illfortunate_spell(void)
{
    set_spell_name("pcurse");
    set_spell_desc("Curse your foe");

    set_spell_element(SS_ELEMENT_LIFE,  40);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_task(TASK_ROUTINE);    

    set_spell_combat_aid(30);

    // Spell effect object
    set_shadow_filename(GUILDDIRSPELL + "obj/pcurse_obj");
}

/*
 * Function: query_illfortunate_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments: The caster of this spell
 */
public string *
query_illfortunate_ingredients(object caster)
{
    return ({ "tiger lily" });
}


public int 
check_valid_action(object caster, mixed *targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Warrior, you " +
           "cannot call upon this curse.\n");
        return 0;
    }

    object *target;

    if (targets[0]->query_prop(ACTIVE_CURSE))
    {
        caster->catch_tell("A curse has already been cast " +
	    "upon "+ COMPOSITE_LIVE(targets) +".\n");
        return 0;
    }

    if (caster->query_prop(DARK_LADY_ASPECT) &&
        targets[0]->query_prop(BLIND_CURSE))
    {
            caster->catch_tell("While under the aspect of the Dark Lady " +
             "you cannot curse a foe affected by pblind.\n");
      return 0;
    }

    if (caster->query_prop(DARK_LADY_ASPECT) &&
        (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun()))))
    {
        if(target[0]->query_pot_cooldown())
            return 1;
   
        caster->catch_tell("While under the aspect of the Dark Lady " +
           "you cannot curse a foe affected by ppain.\n");
        return 0;
    }

    if(BETA_CAID_MOD)
      set_spell_combat_aid(27);
        
    return 1;
}

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_illfortunate(object caster, object* targets)
{
    object tar = targets[0];
    string s = "In the name of Takhisis, Queen of Darkness, by Zeboim of the " +
	"Deep Seas and Chemosh the Lord of Death, by Sargonnas the Dark " +
	"Vengeance, be you cursed!";

    caster->catch_tell("You point at " + tar->query_the_name(caster) +
	" and utter in a cold voice: " + s + "\n");

    tar->catch_tell(caster->query_The_name(tar) + " points at you and " +
	"utters in a cold voice: " + s + "\n");

    tell_room(environment(caster), QCTNAME(caster) + " points at " +
	QTNAME(tar) + " and utters in a cold voice: " + s + "\n",
	({ caster, tar }), caster);
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */

public void
hook_already_has_spell_object(object caster, object target) 
{
    caster->catch_msg(QCTNAME(target) + " is already cursed!\n");
}

/*
 * Function:    hook_curse_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_illfortunate_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " is " +
	"unaffected by your curse.\n");
    targets->catch_msg("You resist an attempt by " + QTNAME(caster) +
	"to curse you.\n");
    caster->tell_watcher(QCTPNAME(caster) + " invocation of a curse was " +
	"resisted by " + COMPOSITE_LIVE(targets) + ".\n",
	({ caster }) + targets); 
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
    object m = caster->query_armour(A_NECK);

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if (!m && !(m->id(MEDALLION_ID)))
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
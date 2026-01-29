/* File         : /d/Gondor/common/guild/newspells/spell_inherit.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22nd 2000
 * Purpose      : This an inheritatble file for all the ranger spells
 * Related Files: ~Genesis/newmagic/spell.c
 * Comments     : All the ranger spells should inherit this file
 *                My thanks to Elessar and Gnadnar for their inital work
 *                on the conversion to the new system, it aided me greatly.
 *                Even more praise to Elessar for the original spells which
 *                the new ones are all based off of.
 * Modifications:
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include "spells.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"
#include <filter_funs.h>
#include <composite.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>

inherit SPELL_LIB;

/* Function name: adjust_valar_disfavor
 * Description  : Adjust the disfavor the Valar have 
 *                for the caster.
 * Arguments    : caster - person who cast the spell
 *                target - who the spell was cast on
 *                factor - a multiplier of the disfavor
 *                         for the casting of a certain spell
 */
void
adjust_valar_disfavour(object caster, object target, float factor)
{
    int disfavour = caster->query_skill(SS_RANGER_DISFAVOUR),
    align = target->query_alignment(),
    amount;

    // Helping an outlaw no matter what their alignment is adds to the
    // disfavour the valar have for this ranger.
    if (!target->query_npc() &&
      (RANGER_DIR + "outlaw")->query_outlaw(target->query_real_name()))
    {
	align -= 500;
	// Assign a minimum value for an outlaw.
	align = min(-200, align);
    }
    // If the target has a positive alignment and the
    // caster has no disfavour no need to continue.
    if (align >= 0 && !disfavour)
	return;

    amount = align / 200;

    amount = ftoi(itof(amount) * factor);

    if (align < 0)
    {
	if (!amount)
	    amount = -1;
	// No need to work with negative numbers
	amount = ABS(amount);
	caster->set_skill(SS_RANGER_DISFAVOUR, disfavour + 
	  max(1, ((100 - disfavour) * amount) / 100));
    }
    else
    {
	if (!amount)
	    amount = 1;
	caster->set_skill(SS_RANGER_DISFAVOUR, disfavour - 
	  max(1, (disfavour * amount) / 100));
    }
    setuid(); seteuid(getuid());
    log_file("disfavour", ctime(time()) + " " + caster->query_name() + " " +
      " disfavour adjusted from " + disfavour + " to " + 
      caster->query_skill(SS_RANGER_DISFAVOUR) + " for casting a spell on " +
      target->query_name() + " of alignment " + align + ".\n");
}

/* Function name: test_for_backfire
 * Description  : See if the spell backfires on the caster. 
 *                The ranger will lose, fatigue, mana, health
 *                or even be banished from the guild.
 * Arguments    : ranger - the ranger casting the spell.
 */
int
test_for_backfire(object caster)
{
    int backfire;

    backfire = caster->query_skill(SS_RANGER_DISFAVOUR) - random(100);

    if (backfire <= 0)
	return 0;

    switch(backfire)
    {
    case 1..25:
	caster->catch_tell("Your call to the Valar for aid, goes unheard.\n");
	caster->add_mana(-(caster->query_max_mana() / 10));
	caster->add_fatigue(-(caster->query_max_fatigue() / 10));
	break;
    case 26..50:
	caster->catch_tell("Your call to the Valar for aid, leaves you "+
	  "feeling mentally drained and physically exhausted.\n");
	caster->add_mana( - (caster->query_max_mana() / 2));
	caster->set_fatigue(0);
	break;
    case 51..70:
	caster->catch_tell("A wave of pain shivers through your body as "+
	  "you call out to the Valar for aid.\n");
	caster->reduce_hit_point(caster->query_max_hp() / 2);
	caster->set_mana(0);
	caster->set_fatigue(0);
	if (caster->query_hp() <= 0)
	    caster->do_die(this_object());
	break;
    default:
	caster->catch_tell("You have brought on the Wrath of the Valar upon " +
	  "yourself for using your talents in aiding the Enemy.\n");
	caster->catch_tell("A wave of instense pain pulses voliently through "+
	  "your body, leaving you feeling cold and alone.\n");
	tell_room(environment(caster), QCTNAME(caster) + " " +
	  " shivers voliently and then slumps over onto the ground.\n",
	  ({caster}));
	caster->set_mana(0);
	caster->set_fatigue(0);
	caster->set_hp(0);
	caster->do_die(this_object());
	(RANGER_DIR + "recruithall")->ban_from_guild(caster,
	  "Wrath of the Valar");
	break;        
    }
    log_file("disfavour", ctime(time()) + " " + caster->query_name() +
      " has spell backfire with result " + backfire + ".\n");
    return 1;
}

/* Function name: concentrate_msg
 * Description  : Generates the message for casting a spell
 * Arguments    : caster  - person casting the spell
 *                targets - things we are casting the spells on.
 *                args    - extra arguments.
 */
void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You start concentrating, focusing on the essence "
      + "of the Valar in the nature around you.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) + " mumbles a few "
      + "ancient words under " + POSSESSIVE(caster) + " breath.\n");
}

/* Function name: hook_use_ingredients
 * Description  : Generates a description on what happens to 
 *                spell ingredients after the spell goes off.
 * Arguments    : ingrs - The ingredients that were sacrificed
 */
void
hook_use_ingredients(object *ingrs)
{
    object what;

    if (sizeof(ingrs))
    {
	if (sizeof(ingrs) > 1)
	    return ::hook_use_ingredients();
	else
	    what = ingrs[0];

	if (what->query_prop(HEAP_S_UNIQUE_ID) == "regrowth_ingredient")
	{
	    write(capitalize(LANG_THESHORT(what)) +" glows briefly, then "+
	      "wiggles out of your hand and digs itself deep into "+
	      "the ground.\n");

	    return;
	}
	if (what->query_prop(OBJ_I_HAS_FIRE))
	{
	    write("Your "+what->short()+" flames up brightly for a moment, "+
	      "and is consumed.\n");
	    return;
	}
	switch(what->query_herb_name())
	{
	case "lothore":
	    write(CAP(LANG_THESHORT(what)) + " withers away and fades " +
	      "into nothingness.\n");
	    break;
	case "redweed":
	    write(CAP(LANG_THESHORT(what)) + " crumples to dust and " +
	      "blows away.\n");
	    break;
	case "athelas":
	    write(CAP(LANG_THESHORT(what)) + " is bathed in a soft light and "+
	      "disappears from your sight.\n");
	    break;
	case "holly berry":
	    write(CAP(LANG_THESHORT(what)) + " burst into a brilliant light, "+
	      "then it is gone.\n");
	    break;
	}
    }
}

/* Function name: default_ranger_spell_setup
 * Description  : This function sets up some defaults and does
 *                some other checks making sure the ranger casting
 *                the spell is able to do so.
 * Arguments    : ranger - the ranger casting the spell
 * Returns      : 1 if everything is ok
 *                0 if setup failed
 */
int
default_ranger_spell_setup(object ranger)
{
    if (ranger->query_skill(SS_PUNISHMENT) == NOSPELLS ||
      ranger->query_skill(SS_PUNISHMENT) == NOABILITIES)
    {
	ranger->catch_tell("You are unable to call upon the Valar "+
	  "for aid for some strange reason.\n");
	return 0;
    }
    if (test_for_backfire(ranger))
    {
	return 0;
    }
    set_spell_fail("Your spell seems to have no effect.\n");
    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);
    // We can move around a bit in order to cast.
    set_spell_stationary(0);
    // We are a peaceful oriented guild.
    set_spell_peaceful(1);
    // We can call apon the aid of the Valar while we can't see.
    set_spell_visual(0);
    return 1;
}

void
hook_combat_fail(object *enemies)
{
    write("You are unable to call upon the aid of the Valar for this "+
      "spell while fighting "+FO_COMPOSITE_ALL_LIVE(enemies, TP) +".\n");
}

void
hook_room_no_magic_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
	write(reason);
    }
    else
    {
	write("For some reason you are uable to call upon the Valar, as "+
	  "if resisted by some strange property within this very room.\n");
    }
}

void
hook_no_mana_fail()
{
    write("You are too mentally exhausted to call upon the Valar.\n");
}

void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You are not properly prepared to call upon the Valar.\n");
}

void
hook_targets_gone()
{
    write("The target of your spell seems to have disappeared.\n");
}

void
hook_stun_fail()
{
    write("You are too stunned to call upon the Valar for aid.\n");
}

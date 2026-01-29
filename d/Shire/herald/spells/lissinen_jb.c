/*
 * Old hin warrior tend speil that was modified for the Heralds of the Valar.
 *
 * Modified by Igneous May 18th 97
 * - Changed Heal to Mana ratio and added some general improvements.
 *
 * Currently this spell will heal someone with 50 SS_LIFE_SKILL and 
 * a 100 guild stat within the heralds 125 - 200 hps with modifers.
 * Healing is increased by 1/3 if casted on someone else besides
 * the caster.
 * -Igneous-
 *
 *  Modified and redone for the new spellcasting system.
 *  Igneous Feb 1998
 */
#include "spells.h"

inherit SPELL_INHERIT;

#define HEAL_AMOUNT(x)   (x->query_skill(SS_ELEMENT_LIFE)  + 25 + \
			 (x->query_stat(SS_LAYMAN) / 2) + random(76))
#define HEAL_MAX         200
#define JOINROOM        (HERALD_DIR + "join")


void
do_lissinen_spell(object caster, object *targets, int *resist, int result)
{
    int amount;
    object target = targets[0];

    if (target->query_hp() == target->query_max_hp())
    {
	caster->catch_tell("Your prayer remains unheard.\n");
	return;
    }

    // No healing naughty people!
    if ((target->query_alignment() < 0))
    {
        caster->catch_msg("Your support of Melkor's servants has angered "+
                          "the Valar.\n");      
//      caster->set_alignment(newalign);
//  	JOINROOM->valar_wrath(QSW);
        return;
    }

    amount = HEAL_AMOUNT(caster);

    // Give a little bonus for thinking of others before ourselves
    if (target != caster)
	amount += amount / 3;
    amount = MIN(amount, HEAL_MAX);

    // Reduce the healing from if they resisted it somewhat.
    if (resist[0])
    {
	amount = amount - ((resist[0] * amount) / 100);
    }

    target->heal_hp(amount);

    if (target == caster)
    {
	caster->catch_tell("You call upon Lorien to tend your wounds.\n");
	tell_room(ENV(caster), QCTNAME(caster) + " calls upon Lorien to "+
	  "tend "+ HIS_HER(caster)+ " wounds.\n", ({caster}));
    }
    else
    {
        caster->catch_msg("You invoke Lorien to tend to "+QCTNAME(target)+
	  ".\n");
	tell_room(ENV(caster), QCTNAME(caster) + " calls upon Lorien to "+
	  "tend to " + QCTNAME(target) + ".\n", ({caster,target}));
	target->catch_msg(QCTNAME(caster) + " calls upon Lorien to tend "+
	  "your wounds.\n");
    }
}

int
create_lissinen_spell(object caster, object *targets, string args)
{
    default_herald_spell_config();
    set_spell_mana(75);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_time(5);
    set_spell_element(SS_ELEMENT_LIFE, 34);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_peaceful(0);
    set_spell_ingredients(({ "huckleberry" }));
    set_spell_effect(do_lissinen_spell);
    set_spell_resist(spell_resist_healing);
}

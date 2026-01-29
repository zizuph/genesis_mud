/*
 * pBlind
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 8;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob, tar = targets[0];

    if (caster->query_wiz_level())
    {
	caster->catch_tell("*** pblind: resist "+resist[0]+", result "+result+" ***\n");
    }

    result = ((100 - resist[0]) * result) / 100;

    if ((result < 5) || P(BLIND_ID,tar))
    {
	caster->catch_tell("You throw up your hands and a stream of black "+
	  "fire flows from your fingers towards "+tar->query_the_name(caster)+
	  "'s eyes. As the stream touches "+HIS(tar)+" eyes, it dissolves.\n");

	all_msgbb(QCTNAME(caster)+" throws up "+HIS(caster)+" hands "+
	  "and a stream of black fire flows from "+HIS(caster)+" fingers "+
	  "towards "+QTNAME(tar)+"'s eyes. As the stream touches "+
	  HIS(tar)+" eyes, it dissolves.\n", caster, tar);

	if (caster->check_seen(tar))
	{
	    tar->catch_tell(caster->query_The_name(tar)+" throws up "+
	      HIS(caster)+" hands and a stream of black fire flows from "+
	      HIS(caster)+" fingers towards your eyes. As the stream touches "+
	      "your eyes, it dissolves and you are left unaffected.\n");
	    if (tar->query_npc() && !tar->query_attack())
		tar->command("$kill "+OB_NAME(caster));
	}
	else if (tar->can_see_in_room())
	{
	    tar->catch_tell("For a brief moment you see only black fire.\n");
	}
	return;
    }

    caster->catch_tell("You throw up your hands and a stream of black " +
      "fire flows from your fingers towards " + tar->query_the_name(caster) +
      "'s eyes. The fire enters " + HIS(tar) + " eyes, blinding " + HIM(tar) +
      ".\n");

    all_msgbb(QCTNAME(caster) + " throws up " + HIS(caster) + " hands " +
      "and a stream of black fire flows from " + HIS(caster) + " fingers " +
      "towards " +QTNAME(tar) + "'s eyes.\n", caster, tar);

    if (caster->check_seen(tar))
    {
	tar->catch_tell(caster->query_The_name(tar) + " throws up " +
	  HIS(caster) + " hands and a stream of black fire flows from " +
	  HIS(caster) + " fingers towards your eyes. The fire enters your " +
	  "eyes and you are blinded!\n");
    }
    else
    {
	tar->catch_tell("Suddenly a black fire enters your eyes and you "+
	  "are blinded!\n");
    }

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(BLIND_OBJ, caster, tar, resist, result);
    ob->set_pblind_time(result);
}

/*
 * pblind_target: a combination of spell_target_one_other_present_living
 * and spell_target_one_present_enemy
 */
public object *
pblind_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
	return spell_target_one_present_enemy(caster, str);
    else
	return spell_target_one_other_present_living(caster, str);
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("pblind");
    set_spell_desc("Blind someone (enemy) temporarily");

    set_spell_time(4);
    set_spell_element(SS_ELEMENT_AIR,   40);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);
    set_spell_mana(65);
    set_spell_task(TASK_ROUTINE);
    set_spell_target(pblind_target);
    set_spell_stationary(0);
    set_spell_target_verify(spell_verify_present); // default 0;

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"eye","gold coin"}));
#endif

    return 0;
}

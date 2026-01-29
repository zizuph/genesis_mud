/*
 * Drain the life-force of a target and bestow some of it upon
 * the mage.
 *
 * November 1996 and August 1997
 * (sautha-, sin - drain, cuith, sin - life)
 * sauthacuith - drain life
 * 
 * Class 3 combat spell
 * Element Death; Form Enchantment
 * Area of effect: one living target
 *
 * Ingredient: attanar, nenamarth potion effect
 * Mana: 50, one third of that on failure.
 * Skills: SS_ELEMENT_DEATH, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description:  Drains SS_CON from the target living if they fail to
 *               resist, granting a portion of that 'life'
 *               (health and stat) to the casting mage for a limited
 *               duration.
 * Resistance:   LIFE_I_UNDEAD, MAGIC_I_RES_DEATH, MAGIC_I_RES_MAGIC
 * Requirements: Morgul Mage, guild level >= 8
 *               mage robe must be present
 *               target may not be undead (automatic resistance)
 *               cannot be cast during combat or while wielding weapons
 */
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#undef DEBUG

#define SAUTHACUITH_SHADOW  "/d/Gondor/common/guild2/spells/obj/sauthacuith_sh.c"
#define MS_SAUTH_INGR     ({ "sauthacuith_ingr1", "sauthacuith_ingr2", })
#define MS_SAUTH_MANA     50
#define MS_SAUTH_TASK     TASK_ROUTINE
#define MS_SAUTH_LIST     ({ SS_SPELLCRAFT, SS_ELEMENT_DEATH, SS_FORM_ENCHANTMENT })

// range of result = 30..120, range of time = 150..600:
#define MS_SAUTH_TIMEMOD   5
#define MS_SAUTH_MAX      10

mixed 
do_sauthacuith(string str) 
{
    object  tp = TP,
	    env = ENV(tp),
           *ingr_arr, 
	   *targets, 
	    target, 
	    shadow_caster,
	    shadow_target;
    string  fail;
    int     is_wiz = tp->query_wiz_level(),
	    diff = MS_SAUTH_TASK,
	    result, 
	    base_stat,
 	    amount;

#if DEBUG
    is_wiz = 0;
#endif

    if (!strlen(str))
	return "Whose life dost thou wish to drain?\n";

    targets = parse_this(LOW(str), "%l");
    if (!sizeof(targets))
	return "Whose life dost thou wish to drain?\n";
    target = targets[0];

    if (sizeof(tp->query_weapon(-1)))
	return "Thou art unable to drain the life of thy victim whilst wielding a weapon!\n";
    if (objectp(tp->query_attack()))
	return "Thou art unable to drain the life of thy victim whilst engaged in combat!\n";

    if (tp->query_sauthacuith_shadow())
	return "Thou art not yet able to drain the life of thy victim again!\n";
    if (target->query_sauthacuith_shadow())
	return "Thou art not able to drain the life of that victim now!\n";

    // is the spell legal for this target, for this target environment?
    if (RNMAGIC(env) || NPMAGIC(target))
	return MORGUL_S_SPELL_FAIL;
    if (!present(MORGUL_S_GUILD_OBJECT, tp))
	return "Without your robe, you cannot cast this spell!\n";
    if (stringp(fail = check_player(tp, MS_SAUTH_INGR, MS_SAUTH_MANA, MS_SAUTH_MIN)))
	return fail;
    ingr_arr = find_ingr(MS_SAUTH_INGR, tp);
    if (!is_wiz && ((result = tp->resolve_task(diff, MS_SAUTH_LIST)) <= 0)) 
    {
#if DEBUG
	write("DEBUG: sauthacuith fail result: " + result + "\n");
#endif
	tp->add_mana(-MS_SAUTH_MANA / 3);
	fail_cast(tp, ingr_arr);
	return 1;
    }

    /*
     * Range for result is -100 .. 180.
     * For maxed skills, it will be centered around 72.
     */
#if DEBUG
    write("DEBUG: sauthacuith result: " + result + "\n");
#endif
    if (result < 30)
	result = 30;
    if (result > 120)
	result = 120;
    // Reduce amount per resistance
    if (target->query_prop(LIVE_I_UNDEAD))
	result = 0;
    else
    {
	result -= (target->query_magic_res(MAGIC_I_RES_MAGIC) * result) / 100;
	result -= (target->query_magic_res(MAGIC_I_RES_DEATH) * result) / 100;
    }
    amount = result / 10;

    if (amount <= 0) 
    {
	tp->catch_msg("Using the power the Dark Lord has bestowed upon you, you draw upon " +
		      "the life-force of " + QTNAME(target) + ", yet receive no response.\n");
	target->catch_msg("Employing Dark Sorcery, " + QTNAME(tp) + " stares coldly at you.\n" +
			  "You feel no effect.\n");
	tell_room(env, "Employing Dark Sorcery, " + QTNAME(tp) + " stares coldly at " +
		  QTNAME(target) + ".\n", ({ tp, target }) );
    } 
    else 
    {
	tp->catch_msg("Using the power the Dark Lord has bestowed upon you, you draw upon " +
		      "the life-force of " + QTNAME(target) + " and imbue it into your own.\n");
	target->catch_msg("Employing Dark Sorcery, " + QTNAME(tp) + " stares coldly at you.\n" +
			  "Your body convulses in nerve-racking pains.\n");
	tell_room(env, "Employing Dark Sorcery, " + QTNAME(tp) + " stares coldly at " +
		  QTNAME(target) + ".\n" + QCTNAME(target) + " screams in agony as " +
		  HIS(target) + " body convulses in pain.\n", ({ tp, target }));

	FIX_EUID;

	shadow_caster = clone_object(SAUTHACUITH_SHADOW);
	shadow_caster->shadow_me(tp);
	shadow_target = clone_object(SAUTHACUITH_SHADOW);
	shadow_target->shadow_me(target);

	shadow_caster->set_sauthacuith_drain( amount, shadow_target);
	shadow_target->set_sauthacuith_drain(-amount, shadow_caster);
	shadow_caster->set_sauthacuith_duration(result * MS_SAUTH_TIMEMOD);
	shadow_target->set_sauthacuith_duration(result * MS_SAUTH_TIMEMOD);
    }

    if (!is_wiz) 
    {
	tp->add_mana(-MS_SAUTH_MANA);
	remove_ingr(ingr_arr);
    }
    
    return 1;
}
#undef DEBUG

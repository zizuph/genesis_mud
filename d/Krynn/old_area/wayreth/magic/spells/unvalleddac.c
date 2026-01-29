/*
 * UnvalLeddac
 *
 * Description: Detect magic
 * Class:       0
 * Ingredients: raspberry
 * Mana:        40 (1/3)
 * Tax:         0.1
 * Skills:      SS_ELEMENT_FIRE     5
 *              SS_FORM_DIVINATION  6
 * Task:        TASK_SIMPLE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

public void unvalleddac_message(object caster, object *targets);

public int
create_spell_unvalleddac(string arg)
{
    string whom, what;

    if (!stringp(arg) || arg == "" )
    {
        write("What do you want to cast the spell on?\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    if (check_combat())
        return 1;

    set_spell_element(SS_ELEMENT_FIRE, 5);
    set_spell_form(SS_FORM_DIVINATION, 6);

    set_spell_time(4);

    set_spell_ingredients("raspberry");

    set_find_target(find_dead_object);
    set_spell_message(unvalleddac_message);
}

public int
do_unvalleddac(string str)
{
    return cast_spell();
}

public void
unvalleddac_message(object caster, object *targets)
{
    object tar = targets[0];

    tell_room(E(caster), QCTNAME(caster) + " chants: " +
	      "Tsaran korilath ith hakon.\n", caster);
    tell_room(E(caster), QCTNAME(caster) + " moves " + POSSESSIVE(caster) +
	      " hand swiftly near the " + tar->query_name() + ".\n", caster);

    caster->catch_msg("You start to chant and at the same time you " +
		      "move your hand swiftly near the " +
		      tar->query_name() + ".\n");

    if (tar->query_prop(MAGIC_AM_MAGIC) ||
	tar->query_prop(MAGIC_AM_ID_INFO) ||
	tar->query_prop(OBJ_I_IS_MAGIC_WEAPON) ||
	tar->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
	sizeof(tar->query_magic_effects()))
    {
        tell_room(E(caster), "The " + tar->query_name() + " starts give off " +
		  "a faint red glow, which only lasts for a short while.\n");
    }
}

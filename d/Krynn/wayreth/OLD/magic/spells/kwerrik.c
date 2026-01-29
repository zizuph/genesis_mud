/*
 * Kwerrik
 *
 * Description: Locate (Show the long-desc of a room of another player)
 * Class:       3
 * Ingredients: two copper coins and horsetail
 * Mana:        34
 * Tax:         0.2%
 * Skills:      SS_ELEMENT_AIR      15
 *              SS_FORM_CONJURATION 19
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

public void kwerrik_message(object caster, object *targets);

public int
create_spell_kwerrik(string arg)
{
    string whom, what;

    if (!stringp(arg) || arg == "")
    {
        write("Whom do you want to locate?\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    if (check_combat())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 15);
    set_spell_form(SS_FORM_CONJURATION, 19);

    set_spell_time(5);
    set_spell_mana(34);

    set_spell_task(TASK_ROUTINE);

    set_spell_stationary();

    set_spell_ingredients("one eye");

    set_find_target(find_distant_living);
    set_spell_message(kwerrik_message);
    set_spell_fail(spell_wohs_fail);
}

public int
do_kwerrik(string str)
{
    return cast_spell();
}

public void
kwerrik_message(object caster, object *targets)
{
    object tar = targets[0];
    int result = query_spell_result()[0];
    string stdfail = "Your mind can't seem to get a firm grip upon " +
                     C(tar->query_real_name()) + ".\n";

    ALLBB(" gets a strange distant look in " + POSSESSIVE(caster) +
	" eyes.");

    if (tar->query_prop(OBJ_M_NO_MAGIC) || E(tar)->query_prop(OBJ_M_NO_MAGIC))
    {
        caster->catch_msg(stdfail);
	return;
    }

    if (tar->query_prop(OBJ_I_RES_MAGIC) > result)
    {
        caster->catch_msg("Strong magic disrupts the locating ability of " +
			  "the spell.\n");
	return;
    }

    GENERALBB("Suddenly an eye appears, it looks around " +
	      "briefly before it disappears as suddenly as it came.",
	      all_inventory(E(tar)));

    caster->catch_msg("Your mind peers across the lands, you get a picture " +
		      "of the area where " + C(tar->query_real_name()) +
		      " is located:\n\n" + E(tar)->long());
}






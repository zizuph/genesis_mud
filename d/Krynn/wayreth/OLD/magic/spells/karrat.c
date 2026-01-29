/*ROOM_M_NO_TELEPORT
 * Karrat
 *
 * Description: Teleport (Teleport myself within the domain)
 * Class:       5
 * Ingredients: (Three herbs)
 * Mana:        34 (+1 for every action done)
 * Tax:         0.3%
 * Skills:      SS_ELEMENT_AIR      24
 *              SS_FORM_DIVINATION  41
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

public void karrat_message(object caster, object *targets);

public int
create_spell_karrat(string arg)
{
    mixed prop;

    if (check_gagged())
        return 1;

    if (check_combat())
        return 1;

    if (!arg || !strlen(arg))
    {
        write("To what destination do you want to teleport?\n");
	return 1;
    }

    if ((prop = E(query_caster())->query_prop(ROOM_I_NO_TELEPORT)))
    {
        write((stringp(prop) ? prop : "This area contains a magical " +
	       "instability that will not allow you to teleport from " +
	       "here.\n"));
	return 1;
    }

    set_spell_element(SS_ELEMENT_AIR, 24);
    set_spell_form(SS_FORM_DIVINATION, 41);

    set_spell_time(7);
    set_spell_mana(72);

    set_spell_task(TASK_ROUTINE);

    set_spell_ingredients(({"fireweed", "basil", "saskatoon"}));

    set_find_target(find_tele_destination);
    set_spell_message(karrat_message);
    set_spell_fail(spell_wohs_fail);
}

public int
do_karrat(string str)
{
    return cast_spell();
}

public void
karrat_message(object caster, object *targets)
{
    ALLBB(" is suddenly gone, and without the slightest sound.");

    caster->catch_msg("You travel through time and space for a short moment " +
		      "and then you feel solid ground under your feet.\n");

    caster->move_living("M", targets[0]);

    ALLBB(" suddenly appears infront of your eyes.");
}






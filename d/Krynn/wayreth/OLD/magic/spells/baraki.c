/*
 * Baraki
 *
 * Description: A shield spell against normal weapons, increases ac.
 *              Will only work on the caster
 * Class:       3
 * Ingredients: myrtleberry and horsetail
 * Mana:        50 (1/3)
* Tax:    0.7
 * Skills:      SS_ELEMENT_FIRE     3
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define BARAKI_OBJ "/d/Krynn/wayreth/magic/obj/baraki"

public void baraki_message(object caster, object *targets);

public int
create_spell_baraki(string arg)
{
    if (stringp(arg) && arg != "" )
    {
        write("You can only use this spell upon yourself.\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_FIRE, 3);
    set_spell_form(SS_FORM_CONJURATION, 4);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(50);
    set_find_target(find_caster);
    set_spell_message(baraki_message);
    set_spell_object(BARAKI_OBJ);
    set_spell_ingredients(({"myrtleberry", "horsetail"}));
}

public int
do_baraki(string str)
{
    return cast_spell();
}

public void
baraki_message(object caster, object *targets)
{
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int t = query_spell_result()[0];
    int size = sizeof(effects);
    
    while(size--)
    {
        if (MASTER_OB(effects[size]) == BARAKI_OBJ)
	{
	    caster->catch_msg("Too late you discover that " +
			      "you already was " +
			      "protected by another shield spell.\n");
            effects[size]->dispel_magic();
	    set_spell_object(0);
	    return;
	}
    }

    tell_room(E(caster), QCTNAME(caster) + " becomes surrounded by " +
	      "a golden glowing aura.\n", caster); 

    
    caster->catch_msg("You surround yourself with a shield spell.\n");

    set_spell_duration(440 + (t > 500 ? 500 : t));
}

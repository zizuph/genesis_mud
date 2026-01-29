/*
 * Takadek
 *
 * Description: A shield spell against normal weapons, increases ac.
 *              Will only work on the caster
 * Class:       3
 * Ingredients: a broken weapon and cladina
 * Mana:        84 (1/3)
* Tax:    0.7
 * Skills:      SS_ELEMENT_FIRE     3
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_EASY
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define TAKADEK_OBJ "/d/Krynn/wayreth/magic/obj/takadek"

public void takadek_message(object caster, object *targets);

public int
create_spell_takadek(string arg)
{
    if (stringp(arg) && arg != "" )
    {
        write("You can only use this spell upon yourself.\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_CONJURATION, 15);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(350);
    set_find_target(find_caster);
    set_spell_message(takadek_message);
    set_spell_object(TAKADEK_OBJ);
    set_spell_ingredients(({"broken weapon", "cladina"}));
}

public int
do_takadek(string str)
{
    return cast_spell();
}

public void
takadek_message(object caster, object *targets)
{
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int t = query_spell_result()[0];
    int size = sizeof(effects);
    
    while(size--)
    {
        if (MASTER_OB(effects[size]) == TAKADEK_OBJ)
	{
	    caster->catch_msg("You are already immune to non-magical" +
			      " weapons!\n");
	    set_spell_object(0);
	    return;
	}
    }

    tell_room(E(caster), QCTNAME(caster) + "'s skin takes on a metallic " +
	      "sheen.\n", caster); 

    
    caster->catch_msg("Cast the spell of protection upon yourself.\n");

    t = (t * caster->query_wohs_level() / 10);

    t = MAX(15, ( t > 120 ? 120 : t ));

    set_spell_duration(t);
}

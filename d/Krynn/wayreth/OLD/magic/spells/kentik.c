/*
 * Kentik
 *
 * Description: Spell of identification
 * Class:       4
 * Ingredients: two copper coins and horsetail
 * Mana:        34
 * Tax:         0.2%
 * Skills:      SS_ELEMENT_AIR     14
 *              SS_FORM_DIVINATION 24
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

public void kentik_message(object caster, object *targets);

public int
create_spell_kentik(string arg)
{
    string whom, what;

    if (!stringp(arg) || arg == "" )
    {
        write("On what do you want to cast the spell?\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    if (check_combat())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 14);
    set_spell_form(SS_FORM_DIVINATION, 24);
    set_spell_stationary();

    set_spell_time(6);
    set_spell_mana(34);

    set_spell_task(TASK_ROUTINE);

    set_spell_ingredients(({"two copper coins", "horsetail"}));

    set_find_target(find_dead_object);
    set_spell_message(kentik_message);
}

public int
do_kentik(string str)
{
    return cast_spell();
}

public void
kentik_message(object caster, object *targets)
{
    object tar = targets[0];
    int result = query_spell_result()[0], size, i;
    mixed magic_info;
    string info = "";

    if (E(tar) == caster)
        tell_room(E(caster), QCTNAME(caster) + " touches one of " +
		  POSSESSIVE(caster) + " items.\n", ({ caster, tar }) );
    else
        tell_room(E(caster), QCTNAME(caster) + " reaches out and touches " +
	      "the " + check_call(tar->short()) + ".\n", 
	      ({ caster, tar}) );

    caster->catch_msg("You touch the " + check_call(tar->short()) + " to " +
		      "get a deeper knowledge about it.\n");


    magic_info = tar->query_prop(MAGIC_AM_ID_INFO);
    size = sizeof(magic_info);

    for (i = 0; i < size; i += 2)
    {
        if (!intp(magic_info[i + 1]))
        {
            LOG("spells", "Corrupt MAGIC_AM_ID_INFO: " + file_name(tar) + 
		".\n");
            break;
        }

        if (magic_info[i + 1] <= result)
        {
            info += (string)magic_info[i];
        }
    }
    
    if (strlen(info))
        caster->catch_msg(info);
    else
    {
        caster->catch_msg("You were not able to reveal anything special " +
			  "about the item. But you however managed to " +
			  "get some other useful information:\n");
	set_this_player(caster);
	tar->appraise_object(result + 50);
    }
}

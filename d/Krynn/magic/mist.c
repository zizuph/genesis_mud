/*
 * Mystic Mist
 *
 * by Rastlin 950603
 */
#include <ss_types.h>
#include <tasks.h>

public object *mist_target(string arg);
public void mist_message(object caster, object target);
public mixed mist_success(object caster, object *targets);

public void
create_spell_mist()
{
    set_element(SS_ELEMENT_WATER, 34);
    set_form(SS_FORM_CONJURATION, 20);

    set_duration(180);
    set_spell_time(5);

    /*    set_ingredients("cotton wool");*/

    set_mana_spell(680);
    set_spell_object("/d/Krynn/rastlin/open/spells2/mist_object");
    set_find_target(mist_target);

    set_spell_task(TASK_ROUTINE);

    set_spell_message(mist_message);
    set_spell_success(mist_success);
}

public int
mystic_mist(string str)
{
    return cast_spell();
}

public object *
mist_target(string str)
{
    if (str && (str != "here"))
        return 0;

    return ({ environment(query_caster()) });
}

public void
mist_message(object caster, object *targets)
{
    tell_room(targets[0], "Suddenly the room becomes " +
	"foggier and foggier.\n", caster);

    caster->catch_msg("You cast the spell and the room becomes " +
	"foggier and foggier.\n");
}

public mixed
mist_success(object caster, object *targets)
{
    int result;

    if ((result = caster->resolve_task(TASK_ROUTINE,
          ({ SS_WIS, SKILL_AVG, SS_SPELLCRAFT, SS_ELEMENT_WATER,
             SS_FORM_CONJURATION, SKILL_END }) )) <= 0)
        return 0;

    return result; 
}





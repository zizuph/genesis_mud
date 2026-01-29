/*
 * Mystic Mist
 *
 * by Rastlin 950603
 */
#include <ss_types.h>
#include <tasks.h>

public object *mist_target(string arg);
public void mist_message(object caster, object target);

public void
create_spell_mist()
{
    set_spell_element(SS_ELEMENT_WATER, 34);
    set_spell_form(SS_FORM_CONJURATION, 20);

    set_spell_duration(180);
    set_spell_time(5);

    /*    set_ingredients("cotton wool");*/

    set_spell_mana(680);
    set_spell_object("/d/Krynn/rastlin/open/spells2/mist_object");
    set_find_target(mist_target);

    set_spell_task(TASK_ROUTINE, 0);

    set_spell_message(mist_message);
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




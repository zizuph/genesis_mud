/*
 * confus
 *
 * Description: Create a fog in the room to confuse exits.
 * Class:       no idea
 * Ingredients: black diamond
 * Mana:        150
 * Tax:         N/A
 * Skills:      SS_ELEMENT_WATER 90
 *              SS_FORM_ILLUSION 70
 * Task:        TASK_DIFFICULT
 * Restriction: The caster must not be engaged in combat.
 */

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "../guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

public object*
spell_target_room(object caster, string argval)
{
    object enemy = caster->query_attack();

    if (!environment(caster))
    {
        caster->catch_tell("You are in the void!\n");
        return ({ });
    }

    return ({ environment(caster) });
}

public varargs int
config_spell(object caster, object *target, string argval)
{
    set_spell_name("confus");
    set_spell_desc("Confuse exits in the room");

    set_spell_element(SS_ELEMENT_WATER, 90);
    set_spell_form(SS_FORM_ILLUSION, 70);

    set_spell_time(7);
    set_spell_task(TASK_DIFFICULT);

    set_spell_mana(150);
    set_spell_target(spell_target_room);
    set_spell_ingredients(({ "black diamond" }));

    set_spell_peaceful(1);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *target, int *resist, int result)
{
    mixed   effect;

    if (!objectp(effect = present("_wohs_fog", environment(caster))))
    {
        caster->catch_tell("You weave an arcane pattern in the air, and" +
            " a heavy fog falls upon the ground.\n");

        tell_room(environment(caster), QCTNAME(caster) + " weaves an" +
            " arcane pattern in the air and a heavy fog falls upon the" +
            " ground.\n", caster);

        effect = make_spell_effect_object(SPELL_OBJ + "fog", caster,
            environment(caster), 0, result);
    }
    else
    {
        caster->catch_tell("You weave an arcane pattern in the air, and" +
            " a fog around you grows denser.\n");

        tell_room(environment(caster), QCTNAME(caster) + " weaves an" +
            " arcane pattern in the air and the fog around " +
            caster->query_objective() + " grows denser.\n", caster);
    }

    /* it will be less effictive to feed the existing fog, than to wait */
    /* for it to disolve and then recast a new one, an abuse prevention */

    effect->set_spell_duration(((result > 180 ? 180 : result) * 3) +
        (effect->query_spell_duration() / 3));
}

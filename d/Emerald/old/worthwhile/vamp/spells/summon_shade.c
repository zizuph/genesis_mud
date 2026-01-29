#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0 - configuration successful
 *                1 - configuration unsuccessful, abort spell
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("shade");
    set_spell_desc("Conjure a shade to serve you");
    set_spell_time(10);
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_ingredients(({}));
    set_spell_resist(0);
    set_spell_peaceful(1);

    return 0;
}

static int
query_casting_success(object caster)
{
    int suc = ::query_casting_success(caster);
    if (suc < 1)
    {
        return suc;
    }

    if (random(100) >= caster->query_skill(SS_FORM_CONJURATION))
    {
        set_spell_fail("No shade answered your summons.\n");
        return 0;
    }

    return suc;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object shade;

    setuid();
    seteuid(getuid());

    shade = clone_object("/d/Emerald/vamp/spells/obj/shade");
    shade->set_owner(caster);

    if (shade->move(environment(caster)))
    {
        shade->remove_object();
        caster->catch_tell("No shade answered your summons.\n");
        return;
    }

    tell_room(environment(shade), QCNAME(shade) + " materializes before " +
        QTNAME(caster) + ".\n", ({ caster }));
    caster->catch_tell(shade->query_Art_name(caster) + " materialized before " +
        "you.\n");
}

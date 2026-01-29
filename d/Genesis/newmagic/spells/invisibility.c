#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

public void
create_spell()
{
    set_spell_name("invisibility");
    set_spell_desc("Turn oneself invisible");
    set_spell_target(spell_target_caster);
    set_spell_time(8);
    set_spell_mana(100);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);
    set_spell_object("/d/Genesis/newmagic/spells/invisibility_obj");

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    string str;
    object *who;

    caster->catch_tell("You begin to concentrate on the spell.\n");

    who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " stands still for a moment, and " +
        caster->query_possessive() + " form begins to shimmer slightly.\n");
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
    object target = targets[0];
    object *before, *after, *met;
    string msg;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }

    before = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result);

    after = FILTER_IS_SEEN(caster, before);
        
    msg = " shimmers and disappears for a just moment before fading back " +
        "into view, though slightly blurred.\n";

    after->catch_msg(QCTNAME(caster) + msg);

    after = before - after;
    /* We have to do this because query_The_name() will return "Someone" */
    met = filter(after, &->query_met(caster));

    msg = " shimmers and disappears from view.\n";
    met->catch_tell(caster->query_Met_name() + msg);
    (after - met)->catch_tell(capitalize(caster->query_nonmet_name()) + msg);

    caster->catch_tell("Your spell takes effect, and you disappear " +
        "from view.\n");
}

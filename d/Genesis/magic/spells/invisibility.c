#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

public void invisibility(object caster, object *targets, int *resist,
    int result);
public void invisibility_conc_msg(object caster, object *targets, string arg);
public int create_spell_invisibility(object caster, object *targets,
    string argument);

public void
add_spell_invisibility()
{
    this_object()->add_spell("invisibility", "Turn oneself invisible",
         create_spell_invisibility, spell_target_caster);
}

/*
 * Function name: create_spelL_invisibility
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_invisibility(object caster, object *targets, string argument)
{
    set_spell_time(8);
    set_spell_mana(100);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(invisibility);
    set_spell_peaceful(1);
    set_spell_conc_message(invisibility_conc_msg);
    set_spell_object("/d/Genesis/magic/spells/invisibility_obj");
    return 0;
}

public void
invisibility_conc_msg(object caster, object *targets, string arg)
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
 * Function name: invisibility
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
invisibility(object caster, object *targets, int *resist, int result)
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

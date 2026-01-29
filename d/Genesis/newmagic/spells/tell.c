/* /d/Genesis/newmagic/spells/tell.c
 * 
 * A default tell spell.
 *
 * Because of the implementation of this spell, specifically relating to the
 * use of the "message" variable, this spell should be cloned individually
 * for each caster instead of sharing the master object among them all.
 * Note that cloned spell objects are not automatically removed by the spell
 * system.  This means that you should be sure to call remove_object() on
 * this spell object when it is no longer needed.
 * See /d/Genesis/newmagic/examples/spell_test.c for example usage.
 */
#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <options.h>
#include <language.h>

private static string message;

public static string
query_tell_message()
{
    return message;
}

public object *
tell_target_one_distant_guild_member(object caster, string str, string guild)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) ||
        !living->query_guild_member(guild) ||
        living->query_wiz_level())
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

public object *
tell_target_one_distant_guild_member_or_known_living(object caster,
    string str, string guild)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) ||
        !(living->query_guild_member(guild) ||
        caster->query_met(living)) ||
        living->query_wiz_level())
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

public object *
find_tell_targets(object caster, string str)
{
    return spell_target_one_distant_known_living(caster, str);
}

public object *
target_tell(object caster, string str)
{
    string who, msg;
    object *targets;

    if (!strlen(str))
    {
        caster->catch_tell("Tell whom what?\n");
        return ({});
    }

    if (!sscanf(str, "%s %s", who, msg))
    {
        caster->catch_tell("What message do you wish to convey?\n");
        return ({});
    }

    if (sizeof(targets = find_tell_targets(caster, who)))
    {
        message = implode(explode(msg, " ") - ({ "" }), " ");
    }

    return targets;
}

public void
create_spell()
{
    set_spell_time(0);
    set_spell_mana(5);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);
    set_spell_ingredients(({}));
    set_spell_resist(0);
    set_spell_name("tell");

    set_spell_target(target_tell);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
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
    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_tell("You tell " +  targets[0]->query_met_name() +
            ": " + query_tell_message() + "\n");
    }

    targets[0]->catch_tell(caster->query_met_name() + " tells you: " + 
        query_tell_message() + "\n");
}

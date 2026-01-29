#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <options.h>
#include <language.h>

private static string message;

public void tell(object caster, object *targets, int *resist,
    int result);
public int create_spell_tell(object caster, object *targets,
    string argument);
public object *target_tell(object caster, string str);

public static string
query_tell_message()
{
    return message;
}

public void
add_spell_tell()
{
    this_object()->add_spell("tell", "Send a message to a distant person",
         create_spell_tell, target_tell);
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
        (living->query_wiz_level() && living->query_invis()))
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
        (living->query_wiz_level() && living->query_invis()))
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

/*
 * Function name: create_spelL_tell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_tell(object caster, object *targets, string argument)
{
    set_spell_time(0);
    set_spell_mana(5);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);
    set_spell_ingredients(({}));
    set_spell_resist(0);
    set_spell_effect(tell);

    return 0;
}

/*
 * Function name: tell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
tell(object caster, object *targets, int *resist, int result)
{
    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_tell("You tell " +  targets[0]->query_met_name() +
            ": " + query_tell_message() + "\n");
    }

    targets[0]->catch_tell(caster->query_met_name() + " tells you: " + 
        query_tell_message() + "\n");
}

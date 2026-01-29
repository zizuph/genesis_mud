
 /*
   * Aeras (Whisper Wind) Spell for the Windwalkers Guild
   * by Jaacar
   * April 24th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <language.h>
#include <options.h>
#include "defs.h"
#include WIND_HEADER

private static string message;

public void aeras(object caster, object *targets, int *resist, int result);
public int create_spell_aeras(object caster, string argument, object *targets);
public object *target_aeras(object caster, string str);
public object *find_aeras_targets(object caster, string str);

public static string
query_aeras_message()
{
    return message;
}

public object *
target_aeras(object caster, string str)
{
    string who, msg;
    object *targets;
    
    if (!present("_aeras_potion_object_",caster))
    {
        write("You are not under the effects of the aeras "+
            "potion!\n");
        return ({});
    }
    
    if (!strlen(str))
    {
        caster->catch_tell("Use the powers of Aeras on whom to say what?\n");
        return ({});
    }

    if (!sscanf(str, "%s %s", who, msg))
    {
        caster->catch_tell("What message do you wish to convey?\n");
        return ({});
    }

    if (sizeof(targets = find_aeras_targets(caster, who)))
    {
        message = implode(explode(msg, " ") - ({ "" }), " ");
    }

    return targets;
}

public object *
spell_target_one_distant_guild_member_or_known_living(object caster,
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
find_aeras_targets(object caster, string str)
{
    return spell_target_one_distant_guild_member_or_known_living(caster, str, GUILD_NAME);
}

public void
create_spell_aeras(object caster, string argument, object *targets)
{
    set_spell_time(3);
    set_spell_mana(64);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR,40);
    set_spell_form(SS_PRAYER,40);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(0);
    set_spell_effect(aeras);
    return 0;
}

public void
aeras(object caster, object *targets, int *resist, int result)
{
    caster->catch_tell("You chant the ancient mantras of Aeras, and "+
        "close your eyes, concentrating on the image of "+
        targets[0]->query_the_name(caster)+" and have the winds relay "+
        "your message for you.\n");
        
    if (caster->query_option(OPT_ECHO))
        caster->catch_tell("Your message was: " + query_aeras_message() +"\n");
    
    tell_room(environment(targets[0]),"A strong wind suddenly begins to "+
        "blow around you.  From within the winds themselves you hear the " +
        "words: " + query_aeras_message() + "\n");
}

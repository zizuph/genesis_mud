/*
  This is the Anemos (tell line) spell for the Worshippers, coded in
  the spell system defined in /d/Genesis/newmagic. 

  Bishop of Calia, June 2003.

  Added condition to not target wizards in busy status.
  Modified Sep 2003, Quintas 

*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spells/tell.c";

#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <options.h>
#include <language.h>
#include <macros.h>
#include "defs.h"

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
        (living->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M) ||
        (living->query_wiz_level() && living->query_invis()))
    {
        if (living->query_guild_name_occ() == "Spirit Circle of Psuchae")
        {
            return ({ living });
        }

        caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
        return ({ });
    }

    return ({ living });
}

//We redefine this to use the built-in targeting function in tell.c.
public object *
find_tell_targets(object caster, string str)
{
    return tell_target_one_distant_guild_member(caster, str,
        "Elemental Worshippers of Calia"); 
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);

    set_spell_time(1);
    set_spell_mana(10);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);

    set_spell_target(target_tell);
    set_spell_name("anemos");
    set_spell_desc("Send a message to a faraway Worshipper.");

    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You begin to murmur the Anemos incantation.\n");
    say(QCTNAME(caster) + " begins to murmur a strange" +
        " incantation.\n");
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
    string name, message;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but feel that your " +
            "message does not reach its target.\n");
        return;
    }
/*
    if (targets[0]->query_wiz_level()) 
    { 
        if ((targets[0]->query_wiz_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M) || targets[0]->query_invis())
        {
            caster->catch_tell("You complete the spell, but feel that your " +
                "message falls on deaf ears.\n");
            return;
        }
    }
*/
    if(targets[0]->query_met(this_player()))
    {
        name = caster->query_name(); // Met? -> 'Bishop'
    }
    else
    {
        name = LANG_ADDART(caster->query_gender_string()) + " " +
           caster->query_race_name(); // Unmet? -> 'a male human'
    }

    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You speak silently into the water and it carries "+
            "your message away.\n");
    }
    else
    {
        caster->catch_tell("You speak silently into the air and it carries your message away.\n");
    }
    
    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_msg("You use the power of Anemos to speak to "+
            QTNAME(targets[0])+": " + query_tell_message () + "\n");
    }
    
    if (environment(targets[0])->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        message = "The water around your ear vibrates carrying "+
            "the voice of " + name + " saying:\n"+
            query_tell_message() +"\n";
    }
    else
    {
        message = "A soft wind blows around your ears carrying "+
            "the voice of " + name + " whispering:\n"+
            query_tell_message() +"\n";
    }
    
    say(QCTNAME(caster)+" places " + caster->query_possessive() + " fingers" +
       " upon " + caster->query_possessive() + " forehead briefly.\n"); 
          
    targets[0]->catch_tell(message);
}



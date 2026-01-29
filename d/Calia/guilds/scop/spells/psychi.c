 
/*
 * psychi.c
 *
 * Psychi (Spirit Talk) spell for the Spirit Circle of Psuchae
 * This is the psychic tell spell (tell line) for the guild.
 *
 * Copyright (C): Jaacar, Jul 23, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Balanced by Navarre August 27th 2006,
 * Set correct mana cost, added ingredient.
 *
 * Updated December 2012 by Petros
 *   (a) allow casting in combat
 *   (b) reveal name of caster when talking to other guild members
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spells/tell.c";

#include <ss_types.h>
#include <options.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>

#include "defs.h"
#include SPIRIT_HEADER

string
query_spell_level()
{
    return "Apprentice";
}

/*
 * Function name: find_tell_targets
 * Description:   Find the target of the spell
 * Arguments:     object caster   - the caster
 *                string str - str argument to the spell invocation
 * Returns:       The target of the spell
 */
public object*
find_tell_targets(object caster, string str)
{
    return spell_target_one_distant_player(caster, str);
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
config_spell(object caster, object* targets, string argument)
{
    set_spell_name("psychi");
    set_spell_desc("Psychic Speech");
    set_spell_time(2);
    set_spell_mana(16);       
    set_spell_visual(0);
    set_spell_vocal(0);
    set_spell_peaceful(0);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_SPIRIT, 25);
    set_spell_form(SS_FORM_DIVINATION, 25);
    set_spell_ingredients(({"silver coin"}));
    set_spell_target(target_tell);
    add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
        
    if (caster->query_intoxicated())
    {
        caster->catch_tell("You cannot use Psuchae's gifts while "+
                           "intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_tell("You cannot use Psuchae's gifts while you are not "+
                           "good aligned.\n");
        return 1;
    }
    ::config_spell(caster, targets, argument);
    return 0;

}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object* targets, string arg)
{
    caster->catch_tell("You concentrate your psychic energies.\n");
    say(QCTNAME(caster) + " appears to concentrate deeply.\n");
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object* targets - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */

public void
resolve_spell(object caster, object* targets, int* resist, int result)
{
    string name;
    object tar = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but feel that your " +
                           "message does not reach its target.\n");
        return;
    }
    
    if (tar->query_wiz_level() && !(IS_MEMBER(tar)))
    {
      	caster->catch_tell("You do not sense " +
          	capitalize(tar->query_name())+
            " presence in the realms.\n");
        return;
    }

    if(tar->query_met(caster) || IS_MEMBER(tar))
    {
        name = caster->query_name();
    }
    else
    {
        name = LANG_ADDART(caster->query_race_name());
    }
    caster->catch_tell("You complete the spell, psychically sending "+
                       "your message to " + tar->query_the_name(caster) +
                       ".\n");
    
    // Send this to GMCP for players who use the Web Client
    caster->gmcp_comms("psychi", 0,
        "The psychic message you sent to " + tar->query_the_name(caster)
      + " was: " + query_tell_message());
    
    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_msg("The psychic message you sent was: " + 
                           query_tell_message() + "\n");
    }
    
    tar->catch_tell("The voice of "+name+" suddenly invades "+
                    "your mind saying: " + query_tell_message() + "\n");
    
    // Send this to GMCP for players who use the web client
    tar->gmcp_comms("psychi", name,
        "The voice of "+name+" suddenly invades "+
        "your mind saying: " + query_tell_message());
}

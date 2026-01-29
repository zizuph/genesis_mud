
/*
 * anakalo.c
 *
 * Anakalo (Word of Recall) spell for the Spirit Circle of Psuchae
 * This will allow a player to 'mark' a place for later, then if one
 * is marked, they can teleport back to it.
 *
 * Copyright (C): Jaacar, August 4th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 *
 * Modifications by Bishop, July 2004.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

#define SPIRIT_TEMPLE_GARDEN "/d/Calia/guilds/scop/temple/garden"
#define SPIRIT_TELEPORT_MAP "/d/Calia/guilds/scop/logs/teleport_store_map"

#define ANAKALO_MODE_TRAVEL 1
#define ANAKALO_MODE_MEMORIZE 2
#define ANAKALO_MODE_RECALL 3
#define ANAKALO_MODE_TEMPLE 4

mapping locationmap = ([ ]);
object comp;
int delay;
int spell_mode = 0;

string
query_spell_level()
{
    return "Master";
}


public object *
special_target_caster(object caster, string str)
{
    int i;
    object *inv = deep_inventory(caster);

    for (i = 0 ; i < sizeof(inv) ; i++)
    {
        if (member_array("_anakalo_component_", inv[i]->query_names()) != -1)
        {
            comp = inv[i];
            break;
        }
    }

    if (!objectp(comp))
    {
        caster->catch_tell("You must have an anakalo component in order to" +
            " cast this spell.\n");
        return ({ });
    }
    
    if (str == "travel")
    {
        if (objectp(caster->query_attack()))
        {
            caster->catch_tell("You can not travel while fighting.\n");
            return ({});
        }
        spell_mode = ANAKALO_MODE_TRAVEL;
        delay = 5;
    }
    else
    if (str == "memorize")
    {
        if (objectp(caster->query_attack()))
        {
            caster->catch_tell("You can not memorize while fighting.\n");
            return ({});
        }    
        spell_mode = ANAKALO_MODE_MEMORIZE;
        delay = 10;
    }
    else
    if (str == "recall")
    {
        spell_mode = ANAKALO_MODE_RECALL;
        delay = 0;
    }
    else
    if (str == "temple")
    {
        spell_mode = ANAKALO_MODE_TEMPLE;
        delay = 1;
    }
    else
    {
        caster->catch_tell("<travel>, <memorize>, <recall> and <temple> are"+
            " the valid arguments to Anakalo.\n");
        return ({});
    }

    return ({caster});    
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
    set_spell_name("anakalo");
    set_spell_desc("Travel");
    set_spell_target(special_target_caster);
    set_spell_time(2);
    set_spell_visual(0);    
    set_spell_mana(150);
    set_spell_vocal(0);
    set_spell_stationary(1);
    set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
    set_spell_element(SS_ELEMENT_SPIRIT, 65);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_ingredients(({}));
    add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);

    if (caster->query_intoxicated())
    {
        caster->catch_msg("You cannot use Psuchae's gifts while intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_msg("You cannot use Psuchae's gifts while you are not "+
            "good aligned.\n");
        return 1;
    }
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
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You summon the energies of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
}


public void
resolve_anakalo(object caster)
{
    setuid();
    seteuid(getuid());

    locationmap = restore_map(SPIRIT_TELEPORT_MAP);

    if (spell_mode == ANAKALO_MODE_MEMORIZE)
    {
        locationmap[caster->query_real_name()] = 
            file_name(environment(caster));
        save_map(locationmap, SPIRIT_TELEPORT_MAP);
        
        caster->catch_tell("You memorize your current location for" +
            " future reference.\n");    
    }
    else
    if (spell_mode == ANAKALO_MODE_RECALL)
    {
        if (!stringp(locationmap[caster->query_real_name()]))
        {
            caster->catch_tell("You have yet to memorize a lcation!\n");
        }
        else
        if (!(find_object(locationmap[caster->query_real_name()])
            ->query_prop(ROOM_I_IS)))
        {
            caster->catch_tell("You cannot recall anything.\n");
        }
        else
        {
            caster->catch_tell("Concentrating deeply, you try to" +
                " picture the location you have memorized:\n" +
                find_object(locationmap[caster->query_real_name()])->long());
        }
    }
    else
    {
        if (environment(caster)->query_prop(ROOM_M_NO_TELEPORT) ||
            environment(caster)->query_prop(ROOM_M_NO_TELEPORT_FROM))
        {
            caster->catch_tell("You feel unable to travel from this location" +
                " with the power of Anakalo.\n");
            return;
        }
        
        if (spell_mode == ANAKALO_MODE_TEMPLE)
        {
            if (file_name(environment(caster)) == SPIRIT_TEMPLE_GARDEN)
            {
                caster->catch_tell("You are already in the Temple garden!\n");
            }
            else
            {
                caster->catch_tell("Picturing the familiar image of the" +
                    " Temple garden in your mind's eye, you invoke the power" +
                    " of Anakalo and close your eyes. Moments later, you open"+
                    " them again and find yourself there.\n");
                tell_room(environment(caster), QCTNAME(caster) + " closes " +
                    caster->query_possessive() + " eyes, then shimmers" +
                    " briefly and is gone.\n", ({caster}));
                caster->move_living("M", SPIRIT_TEMPLE_GARDEN, 1, 0);
                tell_room(environment(caster), QCTNAME(caster) + " appears" +
                    " out of thin air, " + caster->query_possessive() + 
                    " eyes closed. " + capitalize(caster->query_pronoun()) +
                    " opens them again, glancing around.\n", ({caster}));
                
                if (!random(4))
                {
                    //75% chance of component surviving.
                    
                    caster->catch_tell("You sacrificed an anakalo" +
                        " component.\n");
                    comp->set_heap_size(comp->num_heap() - 1);
                }
            }
        }
        else
        {
            if(file_name(environment(caster)) == 
                locationmap[caster->query_real_name()])
            {
                caster->catch_tell("You are already at your memorized" +
                    " location!\n");
            }
            else 
            if (find_object(locationmap[caster->query_real_name()])->
                query_prop(ROOM_M_NO_TELEPORT) ||
                find_object(locationmap[caster->query_real_name()])->
                query_prop(ROOM_M_NO_TELEPORT_TO))
            {
               caster->catch_tell("You feel unable to travel to that" +
                   " location.\n"); 
            }
            else
            {
                 caster->catch_tell("Picturing your memorized location in" +
                     " your mind's eye, you invoke the power of Anakalo" +
                     " and close your eyes. Moments later, you open them" +
                     " again and find yourself there.\n");
                tell_room(environment(caster), QCTNAME(caster) + " closes " +
                    caster->query_possessive() + " eyes, then shimmers" +
                    " briefly and is gone.\n", ({caster}));                     
                caster->move_living("M", 
                    locationmap[caster->query_real_name()], 1, 0);
                tell_room(environment(caster), QCTNAME(caster) + " appears" +
                    " out of thin air, " + caster->query_possessive() + 
                    " eyes closed. " + capitalize(caster->query_pronoun()) +
                    " opens them again, glancing around.\n", ({caster}));
                
                if (!random(2))
                {
                    //50% chance of component surviving.
                    
                    caster->catch_tell("You sacrificed an anakalo" +
                        " component.\n");
                    comp->set_heap_size(comp->num_heap() - 1);
                }                    
            }
        }
    }
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
    string room;
    int old_val, new_val;

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT,(old_val + 6));

    set_alarm(itof(delay), 0.0, &resolve_anakalo(caster));
}

/*
 * vekpos.c
 *
 * Vekpos (Turn Undead) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, September 1st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Fixed problem with the component. Can't have it taking just
 * any skull. - Bishop, April 2004.
 *
 * Further modifications - Bishop, April 2004.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

#define I_HAVE_BEEN_SPIRIT_TURNED "_i_have_been_spirit_turned"
#define TURN_LOG "spirit_circle/spirit_undead_turn_log"

object comp;

public object *
special_target_one_present_living(object caster, string str)
{
    object *oblist, *skull;

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }
    
    oblist = PARSE_THIS(str,"[at] / [on] [the] %l");
        
    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only "+
            "select one target.\n");
        return ({});
    }


    skull = filter(deep_inventory(caster), &operator(==)("skull")  @ 
        &->query_organ());
        
    if (!sizeof(skull))
    {
        caster->catch_tell("You need a skull in order to successfully" +
            " cast this spell!\n");
        return ({ });
    }
    
    comp = skull[0];        
        
    return oblist;
}


string
query_spell_level()
{
    return "Apprentice";
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
    if (caster == 0)
    {
        set_spell_name("vekpos");
        set_spell_desc("Turn Undead");
        set_spell_target(special_target_one_present_living);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(2);
        set_spell_mana(25);
        set_spell_vocal(0);
        set_spell_offensive(1);
        set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
        set_spell_resist_task(TASK_FORMIDABLE);
        set_spell_element(SS_ELEMENT_SPIRIT, 40);
        set_spell_form(SS_FORM_DIVINATION, 40);
        set_spell_ingredients(({})); //Component defined in target routine.
        set_spell_object(SPIRIT_SPELLS + "vekpos_ob");        
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
    else
    {
        if (!targets[0]->query_npc() && (targets[0]->query_ghost() || 
            !interactive(targets[0])))
        {
            caster->catch_tell("You cannot use this gift on a ghost.\n");
            return 1;
        }
        if (!targets[0]->query_prop(LIVE_I_UNDEAD))
        {
            caster->catch_tell(targets[0]->query_The_name(caster)+" is not undead!\n");
            return 1;
        }

        return 0;
    }
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
    caster->catch_tell("You concentrate on the powers of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
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
    int old_val, new_val, caster_strength, undead_strength;
    object spellob;

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 2));
    caster->set_skill(SS_SPELLS_CASTED, new_val);    

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
            " unaffected.");
        return;
    }

    caster->catch_tell("Brandishing your sacred mandala, you call out to" +
        " Psuchae to aid you in removing the abomination that is " +
        targets[0]->query_the_name(caster) + " from your sight!\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) + " brandishes "+
        caster->query_possessive() + " sacred mandala in your direction, " + 
        caster->query_possessive() + " face a mask of anger and disgust at" +
        " your presence.\n");
    tell_room(environment(caster), QCTNAME(caster) + " brandishes " + 
        caster->query_possessive() + " sacred mandala in " + 
        LANG_POSS(QTNAME(targets[0])) + " direction, " +
        caster->query_possessive() +" face a mask of anger and disgust at " + 
        LANG_POSS(QTNAME(targets[0]))+ " presence.\n", (({caster, targets[0]})));

    caster_strength = caster->query_stat(SS_WIS) + caster->query_stat(SS_OCCUP)
        + caster->query_casting_bonus();
    caster_strength = caster_strength + random(caster_strength)/2 +
        random(caster_strength)/2;
    undead_strength = 2*(targets[0]->query_prop(LIVE_I_UNDEAD)) +
        targets[0]->query_stat(SS_DIS);
    undead_strength = undead_strength + random(undead_strength)/2 +
        random(undead_strength)/2;
    if (caster_strength > undead_strength)
    {
        if (2*caster_strength > undead_strength + targets[0]->query_hp())
        {
            caster->catch_tell(targets[0]->query_The_name(caster) + " is" +
                " completely destroyed by your prayer! " + 
                capitalize(targets[0]->query_possessive()) + " body" +
                " disintegrates into dust and disperses.\n");
            targets[0]->catch_tell("Pain and light floods your world. Your" +
                " last feeling is of your body disintegrating.\n");
            tell_room(environment(caster), QCTNAME(targets[0]) + " is" +
                " completely destroyed! " +        
                capitalize(targets[0]->query_possessive()) + " body" +
                " disintegrates into dust and disperses.\n", (({caster,
                targets[0]})));
            setuid();
            seteuid(getuid());
            write_file(SPIRIT_LOGS + "vekpos_slay_log", ctime(time()) + ": " + 
                caster->query_name() + " slew " + targets[0]->query_real_name()
                + ", who had " + targets[0]->query_hp() + " left.\n");              
            targets[0]->add_prop(LIVE_I_NO_CORPSE, 1);
            targets[0]->set_hp(0);
            targets[0]->do_die(caster);
        } 
        else
        if (targets[0]->query_prop(NPC_I_NO_RUN_AWAY))
        {
            tell_room(environment(caster), QCTNAME(targets[0]) + " looks" +
                " shaken, but does not run.\n", (({targets[0]})));
        }
        else 
        {
            setuid();
            seteuid(getuid());
            spellob = make_spell_effect_object(query_spell_object(), caster, 
                targets[0], resist[0], result);
            spellob->move(targets[0], 1); 
        }
    }
    else
    {
        caster->catch_tell(targets[0]->query_The_name(caster) + " smirks" +
            " in amusement at your antics.\n");
        targets[0]->catch_tell("You smirk in amusement at " + 
            LANG_POSS(caster->query_the_name(targets[0])) + " antics.\n");
        tell_room(environment(caster), QCTNAME(targets[0]) + " smirks in" +
            " amusement at " + LANG_POSS(QTNAME(caster)) + " antics.\n",
            (({caster, targets[0]})));
    }

    caster->catch_tell("You sacrificed a skull.\n");
    comp->set_heap_size(comp->num_heap() - 1);
}
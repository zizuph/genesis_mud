/*
 * apergo.c
 *
 * Apergo (Soul Strike) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Updates by Bishop - April 2004.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spells/harm";
 
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "defs.h"
#include SPIRIT_HEADER

object comp;
 
string
query_spell_level()
{
    return "Master";
}

public object*
special_target_one_other_present_living(object caster, string str)
{
    object *oblist;

    object *gems = filter(deep_inventory(caster), &operator(==)("ruby") @ 
        &->query_gem_name());

    if (!sizeof(gems))
    {
        caster->catch_tell("You need a red ruby in order to successfully" +
            " cast this spell!\n");
        return ({ });
    }
    
    comp = gems[0];

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

    if (oblist[0]->query_prop(LIVE_I_UNDEAD))
    {
        caster->catch_tell("Soul strike does not affect the soulless!\n");
        return ({});        
    }

    return oblist;
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
    set_spell_name("apergo");
    set_spell_desc("Soul Strike");
    set_spell_element(SS_ELEMENT_SPIRIT, 65);
    set_spell_form(SS_FORM_ENCHANTMENT,60);
    set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
    set_spell_ingredients(({}));
    set_spell_time(4);    
    set_spell_target(special_target_one_other_present_living);
    set_spell_target_verify(spell_verify_present);
    set_spell_mana(75);
    set_harm_pen(100);
    set_spell_vocal(0);
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
    int i, gstat, wisdom, alignment, total, old_val, new_val;
    mixed *hitresult;

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT,(old_val + 6));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    gstat = caster->query_stat(SS_OCCUP);
    wisdom = caster->query_stat(SS_WIS);
    alignment = targets[0]->query_alignment();

    total = (gstat + wisdom)/2 + caster->query_casting_bonus()/2;
    total = total + random(total)/2 + random(total)/2;
    
    if (total > 500)
    {
        total = 500 + (total-500)/3;
    }
    
    total = MAX(total, 200);
    
    //Now total is a number roughly in the 200-500 range. 
    
    if (alignment >= 0)
    {
        total = 0;
        //No damage for goodies!
    }
    else
    {
        total += MIN(500*ABS(alignment)/1000, 500);
        //Add a number from 0 to 500 dependant on how evil they are.
    }
    
    set_harm_pen(total);

    desc_harm_cast(caster, targets);
    
    if (caster->query_wiz_level())
    {
        caster->catch_msg("The pen was: "+total+".\n");
    }

    for (i = 0; i < sizeof(targets); i++)
    {
        hitresult = do_harm_damage(caster, targets[i], 
            harm_pen * (100 - resist[i]) / 100);
        desc_harm_damage(caster, targets[i], hitresult);
         
        if (targets[i]->query_hp() <= 0)
        {
            targets[i]->do_die(caster);
        }
    }
    
    if (random(100) >= 90)
    {
            caster->catch_tell("You sacrificed a red ruby.\n");
            comp->set_heap_size(comp->num_heap() - 1);
    }          
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_harm_damage() call.
 */

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string how1, how2, how3;
    
    switch (result[0])
    {
        case 0:
            how1 = target->query_The_name(caster) + " looks slightly" +
                " uncomfortable.\n";
            how2 = QCTNAME(target) + " looks slightly uncomfortable.\n";
            how3 = "You feel slightly uncomfortable under " + 
                caster->query_possessive() + " gaze.\n";
            break;
        case 1..7:
            how1 = target->query_The_name(caster) + " looks distraught" +
                " as you force " + target->query_objective() + " to relive" +
                " memories from " + target->query_possessive() + " life of" +
                " evil. Minor wounds open various places on " + 
                target->query_possessive() + " body.\n";
            how2 = QCTNAME(target) + " looks distraught under " + 
                LANG_POSS(QTNAME(caster)) + " gaze, minor wounds opening" +
                " various places on " + target->query_possessive() + 
                " body.\n";
            how3 = "You feel distraught as " + caster->query_the_name(target) +
                " forces you to relive memories from your life of evil. Minor"+
                " wounds open various places on your body.\n";
            break;
       case 8..15:
           how1 = target->query_The_name(caster) + " shrinks from your gaze" +
               " as you force " + target->query_objective() + " to experience"+
               " some of the pain " + target->query_pronoun() + " has" +
               " inflicted upon others. The intensity of the emotion causes" +
               " wounds to appear all over " + target->query_possessive() +
               " body.\n";
           how2 = QCTNAME(target) + " shrinks from " + 
               LANG_POSS(QTNAME(caster)) + " gaze, wounds opening all over " +
               target->query_possessive() + " body.\n";
           how3 = "You shrink from " +LANG_POSS(caster->query_the_name(target))
               + " gaze as " + caster->query_pronoun() + " forces you to" +
               " experience some of the pain you have inflicted upon others." +
               " The intensity of the emotion causes wounds to appear all" +
               " over your body.\n";
           break;
       case 16..30:
           how1 = "You sense pain blossoming within " + 
               target->query_The_name(caster) + " as you make " +
               target->query_objective() + " feel how " +
               target->query_possessive() + " life of evil has hurt others." +
               " The traumatizing experience causes " + 
               target->query_objective() + " to stagger.\n";
           how2 = QCTNAME(target) + " looks devastated under " +
               LANG_POSS(QTNAME(caster)) + " gaze, tears welling up in " +
               target->query_possessive() + " eyes as the mental and" +
               " physical pain causes " + target->query_objective() +
               " to stagger.\n";
           how3 = "Pain blossoms within you as " + 
               caster->query_the_name(target) + " makes you feel how your" +
               " life of evil has hurt others. The traumatizing experience" +
               " causes you to stagger.\n";
           break;
       default:
           how1 = target->query_The_name(caster) + " is overcome by pangs of" +
               " sadness and weeps uncontrollably as you force " +
               target->query_objective() + " to repent " +
               target->query_possessive() + " life of evil. " +
               capitalize(target->query_possessive()) + " physical body is" +
               " barely hanging on under the stress of the emotion.\n";
           how2 = QCTNAME(target) + " weeps uncontrollably under " + 
               LANG_POSS(QTNAME(caster)) + " gaze, " + 
               target->query_possessive() + " body barely hanging on under" +
               " the stress of the emotion.\n";
           how3 = "You are overcome by pangs of sadness, and weep" +
               " uncontrollably as " + caster->query_the_name(target) + 
               " forces you to repent your life of evil. Your physical body" +
               " is barely hanging on under the stress of the emotion.\n";
    }
    
    if (target->query_hp() <= 0)
    {
        how1 = target->query_The_name(caster) + " screams shrilly as you" +
            " force " + target->query_objective() + " to realize the futility"+
            " of " + target->query_possessive() + " life of evil. " +
            capitalize(target->query_possessive()) + " body gives up as the" +
            " will to live drains from " + target->query_objective() + ".\n";
        how2 = QCTNAME(target) + " screams shrilly under " + 
            LANG_POSS(QTNAME(caster)) + " gaze, " + target->query_possessive()
            + " face turning ashen grey. " + 
            capitalize(target->query_pronoun()) + " crumples lifelessly to" +
            " the ground shortly thereafter.\n";
        how3 = "You scream shrilly as " + caster->query_the_name(target) + 
            " forces you to realize the futility of your life of evil. Your" +
            " body gives up as the will to live drains from you, and blissful"+
            " darkness follows soon thereafter.\n";
    }
    
    
    setuid();
    seteuid(getuid());
    write_file(SPIRIT_LOGS + "apergo_damage_log", ctime(time()) + ": " + 
        caster->query_name() + " cast a " + harm_pen + " pen Apergo," +
            " dealing " + result[3] + " damage.\n");

    
    caster->catch_tell(how1);
    caster->tell_watcher(how2, target);
    target->catch_tell(how3);
}


/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */

public void
desc_harm_cast(object caster, object *targets)
{
    int align = targets[0]->query_alignment();
    string souldesc;
    
    if (align >= 0)
    {
        align = 0;
    }
    
    switch (ABS(align))
    {
        case 0:
            souldesc = "";
            break;
        case 1..300:
            souldesc = " blemished";
            break;
        case 301..600:
            souldesc = " tainted";
            break;
        case 601..900:
            souldesc = " rotten";
            break;
        default:
            souldesc = " pitch-black";
    }
 
    caster->catch_tell("Drawing upon the power of Psuchae, you gaze at " +
        targets[0]->query_the_name(caster) + ". You weigh and judge " +
        targets[0]->query_objective() + ", trying to force " +
        targets[0]->query_possessive() + " body to become a reflection of " +
        targets[0]->query_possessive() + souldesc + " soul.\n");

    caster->tell_watcher(QCTNAME(caster) + " fixes " + QTNAME(targets[0]) +
        " with a steely gaze, " + caster->query_possessive() + " eyes starting" +
        " to shimmer and turning into a brilliant silver.\n", targets[0]);

    targets[0]->catch_tell(caster->query_The_name(targets[0]) + " fixes you" +
        " with " + caster->query_possessive() + " gaze, " + 
        caster->query_possessive() + " eyes starting to shimmer and turning" +
        " into a brilliant silver. You feel " + caster->query_objective() + 
        " weighing and judging you.\n");
    
}



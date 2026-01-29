/*

  This is the spell object for the Dynami spell for the Worshippers.

  Coded by Bishop of Calia, June 2003.

 */
 
#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

int *boosts = ({ 0, 0, 0});

// Utility Functions for Determining Bonus. Strength bonuses do not scale
// linearly. So we have to determine the strength bonus based on the amount
// of actual combat aid that it grants. This function is similar to the one
// being used by the Knight's kheroism effect and the Gladiator berserk
// effects.
// NOTE: Do not use this function yet until after balance effects have
//       been determined. Dynami is very much overpowered already.
//       As a result, this function will end up boosting the worshippers
//       effects even more than it already does. Layman should not gain more
//       than 50% combat aid.
public int
query_stat_bonus(object player, int stat, int boost_percentage)
{
    // The goal of this function is to increase the F_STR_FACTOR aid
    // by 20%. This is done by modifying and plugging in the numbers
    // based on the current F_STR_FACTOR formula: ((600 + (str) * 4) / 10)    
    int base, modifier;
    float boost;
    
    base  = player->query_base_stat(stat) + player->query_stat_extra(stat);
    boost = 1.0 + itof(boost_percentage) / 100.0; // should give something like 1.20
    modifier = ftoi(150.0 * (boost - 1.0) + (itof(base) * boost));    
    
    return modifier - base;
}

public int
start()
{
    int boost;
    string desc1, desc2;

    set_spell_effect_desc("stat boost");
    
/*
    The results should be between 10 and 30 percent bonus to the STR, CON
    and DIS stats. 
    
    There are two steps to determining this.
    1. First, do a random against their layman guildstat to get a value between 10 and 15
    2. Second, add 5 if their earth element skill is good enough
*/
        
    boost = min(10 + random(spell_caster->query_stat(SS_LAYMAN))/10
        + random(spell_caster->query_stat(SS_LAYMAN))/10, 25);
    
    if (spell_caster->resolve_task(TASK_ROUTINE, 
        ({SS_ELEMENT_EARTH, TS_WIS})) >= 80)
    {
        boost+= 5;
    }

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_tell("Stat increase is: " + boost + " percent.\n");
    }
    
    // Get the actual value of their boosts and put it into the boosts array. We don't
    // use query_stat because that number includes delta_stat, which is temporary stats
    // that are added by alarm.
    boosts[0] = ((spell_target->query_base_stat(SS_STR) + spell_target->query_stat_extra(SS_STR))
              * boost) / 100;
    boosts[1] = ((spell_target->query_base_stat(SS_CON) + spell_target->query_stat_extra(SS_CON))
              * boost) / 100;
    boosts[2] = ((spell_target->query_base_stat(SS_DIS) + spell_target->query_stat_extra(SS_DIS))
              * boost) / 100;

    // Add the boosts to their existing stat extras
    spell_target->set_stat_extra(SS_STR, spell_target->query_stat_extra(SS_STR) + boosts[0]);
    spell_target->set_stat_extra(SS_CON, spell_target->query_stat_extra(SS_CON) + boosts[1]);    
    spell_target->set_stat_extra(SS_DIS, spell_target->query_stat_extra(SS_DIS) + boosts[2]);

//Caster will be hurt from getting extra hit points, so heal him/her:

    spell_target->heal_hp(20 * boosts[1]);
    
    spell_target->add_prop(LIVE_I_DYNAMI_BOOST, 1);

    spell_caster->catch_tell("You call out to Lady Gu, asking her to" +
        " let you partake in her strength!\n");
    if (boost < 18)
    {
        desc1 = "You feel your resolve harden as you realise Lady Gu has" +
            " granted your prayer. Your body toughens and your arms flex" +
            " with newfound strength!\n";
        desc2 = " appears strengthened.\n";
    }
    else if (boost < 26)
    {
        desc1 = "A great calm washes over you as you realise that your" +
            " Patron Lady has granted your prayer. Your body feels as heavy" +
            " as if it were made out of the earth itself, yet you can move" +
            " with undiminished speed!\n";
        desc2 = " appears greatly strengthened.\n";
    }
    else
    {
        desc1 = "With the realisation that Lady Gu has granted your prayer," +
            " you feel tranquility penetrate your being. Your body feels as" +
            " massive as a granite statue, yet you can move your arms and" +
            " legs as if they were lighter than feathers!\n";
        desc2 = " begins to move with great strength and determination!\n";
    }

    spell_caster->catch_tell(desc1);
    say(QCTNAME(spell_caster) + desc2, spell_caster);

    set_alarm(360.0, 0.0, dispel_spell_effect);

    return 1;
}


varargs public int
dispel_spell_effect(object dispeller)
{
    spell_caster->catch_tell("The enchantment granted by Lady Gu" +
        " dissipates, and your body and mind return to normal.\n");
    say(QCTNAME(spell_caster) + " appears to weaken somewhat.\n",
        spell_caster);

    spell_target->set_stat_extra(SS_STR, 
        spell_target->query_stat_extra(SS_STR) - boosts[0]);
    spell_target->set_stat_extra(SS_CON, 
        spell_target->query_stat_extra(SS_CON) - boosts[1]);    
    spell_target->set_stat_extra(SS_DIS, 
        spell_target->query_stat_extra(SS_DIS) - boosts[2]);
    
    spell_target->remove_prop(LIVE_I_DYNAMI_BOOST);

    spell_target->add_prop(LIVE_I_HAD_DYNAMI_BOOST, 1);

    remove_spell_effect_object();

    return 1;
}
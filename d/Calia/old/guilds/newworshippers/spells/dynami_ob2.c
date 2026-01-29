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

public int
start()
{
    int boost;
    string desc1, desc2;

    set_spell_effect_desc("stat boost");
    
/*
    The results should be between 10 and 30 percent bonus to the STR, CON
    and DIS stats. 
*/

    boost = min(10 + random(spell_caster->query_stat(SS_LAYMAN))/8
        + random(spell_caster->query_stat(SS_LAYMAN))/8, 30);

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_tell("Stat increase is: " + boost + " percent.\n");
    }

    boosts[0] = boost*(spell_target->query_base_stat(SS_STR) + 
        spell_target->query_stat_extra(SS_STR))/100;
    boosts[1] = boost*(spell_target->query_base_stat(SS_CON) + 
        spell_target->query_stat_extra(SS_CON))/100;   
    boosts[2] = boost*(spell_target->query_base_stat(SS_DIS) + 
        spell_target->query_stat_extra(SS_DIS))/100;

    spell_target->set_stat_extra(SS_STR, boosts[0] + 
        spell_target->query_stat_extra(SS_STR));
    spell_target->set_stat_extra(SS_CON, boosts[1] + 
        spell_target->query_stat_extra(SS_CON));    
    spell_target->set_stat_extra(SS_DIS, boosts[2] + 
        spell_target->query_stat_extra(SS_DIS));
    
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
    say(LANG_POSS(QCTNAME(spell_caster)) + " appears to weaken somewhat.\n",
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
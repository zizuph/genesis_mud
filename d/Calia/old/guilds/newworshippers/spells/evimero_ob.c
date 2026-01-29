/*
  This is the spell object for the Evimero (haste) spell for the
  Worshippers.

  Coded by Bishop of Calia, June 2003.

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"


int speed;

public int
start()
{
    string desc1, desc2;

    set_spell_effect_desc("haste");
    
/*
    We want the results here to vary from between LIVE_I_QUICKNESS 
    addition of 40 and 100. 125 represents doubled speed.  
*/

    speed = min(40 + random(spell_caster->query_stat(SS_LAYMAN))/3
        + random(spell_caster->query_stat(SS_LAYMAN))/3, 100);

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_tell("Speed increase is: " + speed + ".\n");
    }

    spell_target->add_prop(LIVE_I_QUICKNESS, 
        (int)spell_target->query_prop(LIVE_I_QUICKNESS) + speed);
    spell_target->add_prop(LIVE_I_EVIMERO_HASTE, 1);

    spell_caster->catch_tell("You call out to Lady Aeria, asking her to" +
        " make you into her avenging wind!\n");
    if (speed < 65)
    {
        desc1 = "The world around you suddenly slows and all seems to move" +
            " sluggishly. You retain your speed though, and prepare to lay" +
            " into your foes!\n";
        desc2 = "with greater speed!\n";
    }
    else if (speed < 90)
    {
        desc1 = "Suddenly all about you seems to slow down markedly. The" +
            " world lurches around as if caught in syrup, yet you move like" +
            " the wind and get ready to savage your enemies!\n";
        desc2 = "with much greater speed!\n";
    }
    else
    {
        desc1 = "Your environment suddenly screeches almost to a halt." +
            " Friend and foe alike inch about as if stuck in some" +
            " grotesque dance, yet you feel revitalised and prepare to" +
            " descend on those who oppose you with the fury of the" +
            " whirlwind!\n";
        desc2 = "like the wind!\n";
    }

    spell_caster->catch_tell(desc1);
    say(QCTNAME(spell_caster) + " suddenly begins to move " + desc2, 
        spell_caster);

    set_alarm(240.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_caster->catch_tell("The enchantment granted by Lady Aeria" +
        " dissipates, and the world around you seems to move normally" +
        " again.\n");
    say(LANG_POSS(QCTNAME(spell_caster)) + " movements slow down.\n",
        spell_caster);

    spell_target->add_prop(LIVE_I_QUICKNESS, 
        (int)spell_target->query_prop(LIVE_I_QUICKNESS) - speed);
    spell_target->remove_prop(LIVE_I_EVIMERO_HASTE);
    spell_target->add_prop(LIVE_I_HAD_EVIMERO_HASTE, 1);

    remove_spell_effect_object();

    return 1;
}
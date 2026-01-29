
/* Blindness Object

   Conjured by the Tuphlono spell of the Firewalkers.

   Coded by Jaacar 

*/

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("blindness");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) -10);

    set_alarm(40.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (objectp(spell_target)) { 
        spell_target->add_prop(LIVE_I_SEE_DARK,
            (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 10);
        spell_target->catch_tell("You finally "+
            "regain your sight.\n");
        tell_room(environment(spell_target),QCTNAME(spell_target)+
            " appears to have regained "+spell_target->query_possessive()+
            " sight.\n",({spell_target}));
    } 

    remove_spell_effect_object();

    return 1;
}


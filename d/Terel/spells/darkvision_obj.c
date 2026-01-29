inherit "/d/Genesis/newmagic/spell_effect_object";

#include <stdproperties.h>

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("darkvision");

    spell_target->add_prop(LIVE_I_SEE_DARK, 
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 10);

    set_alarm(600.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) - 10);

    remove_spell_effect_object();

    return 1;
}

inherit "/d/Genesis/newmagic/spell_effect_object";

#include <stdproperties.h>

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    int base_stat;

    set_spell_effect_desc("blindness");

    spell_target->add_prop(LIVE_I_SEE_INVIS,
        spell_target->query_prop(LIVE_I_SEE_INVIS) - 1000);
    set_alarm(30.0, 0.0, dispel_spell_effect);
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (spell_target)
    {
        spell_target->add_prop(LIVE_I_SEE_INVIS,
            spell_target->query_prop(LIVE_I_SEE_INVIS) + 1000);
        spell_target->catch_tell("You can see again.\n");
    }

    remove_spell_effect_object();
    return 1;
}

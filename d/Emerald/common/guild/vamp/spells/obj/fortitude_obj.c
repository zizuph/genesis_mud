inherit "/d/Genesis/newmagic/spell_effect_object";

#include "../spells.h"
#include <ss_types.h>

#define STR_FORMULA(f) (f / 2)

int fortitude = 0;

varargs public int dispel_spell_effect(object dispeller);

public void
set_fortitude(int f)
{
    fortitude = f;
}

public int
start()
{
    set_spell_effect_desc("fortitude");

    spell_target->set_stat_extra(SS_STR,
        spell_target->query_stat_extra(SS_STR) + STR_FORMULA(fortitude));
    spell_target->add_prop(VAMP_I_FORTITUDE, STR_FORMULA(fortitude));
    set_alarm(30.0, 0.0, dispel_spell_effect);
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The strength fades.\n");
    spell_target->set_stat_extra(SS_STR,
        spell_target->query_stat_extra(SS_STR) - STR_FORMULA(fortitude));
    spell_target->remove_prop(VAMP_I_FORTITUDE);
    remove_spell_effect_object();
    return 1;
}

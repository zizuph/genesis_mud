inherit "/d/Genesis/newmagic/spell_effect_object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

int dark = 0;

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("darkness");

    dark = min(4, max(1, spell_caster->query_effective_vamp_stat() / 40));
    spell_target->add_prop(CONT_I_LIGHT,
        spell_target->query_prop(CONT_I_LIGHT) - dark);
    set_alarm(30.0, 0.0, dispel_spell_effect);
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (spell_target)
    {
        spell_target->add_prop(CONT_I_LIGHT,
            spell_target->query_prop(CONT_I_LIGHT) + dark);

        spell_target->catch_tell("Your dark aura fades.\n");
        tell_room(environment(spell_target), QCTPNAME(spell_target) +
            "dark aura fades.\n");
    }

    remove_spell_effect_object();
    return 1;
}

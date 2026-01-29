inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#include <ss_types.h>

int aware, steal;

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    int base_stat;

    set_spell_effect_desc("perception");

    if (!shadow_me(spell_target))
    {
        return 0;
    }

    base_stat = spell_caster->query_effective_vamp_stat() - 80;
    aware = base_stat / 2;
    spell_target->add_skill_extra(SS_AWARENESS,
        spell_target->query_skill_extra(SS_AWARENESS) + aware);
    steal = min(100, base_stat);

    set_alarm(30.0, 0.0, dispel_spell_effect);
    return 1;
}

public int
hook_victim_no_steal_bonus(object item)
{
    return steal;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (spell_target)
    {
        spell_target->set_skill_extra(SS_AWARENESS,
            spell_target->query_skill_extra(SS_AWARENESS) - aware);

        spell_target->catch_tell("Your dark aura fades.\n");
    }

    remove_spell_effect_object();
    return 1;
}

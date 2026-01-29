inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("invisibility");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    if (!shadow_me(spell_target))
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->add_prop(OBJ_I_INVIS, 
        (int)spell_target->query_prop(OBJ_I_INVIS) + 1);

    set_alarm(900.0, 0.0, dispel_spell_effect);

    return 1;
}

public int
check_vis(object target, object onlooker)
{
    return (CAN_SEE_IN_ROOM(onlooker) &&
        CAN_SEE(onlooker, target));
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object *nosee = filter(all_inventory(environment(spell_target)) -
        ({ spell_target }), not @ &check_vis(spell_target));

    spell_target->add_prop(OBJ_I_INVIS,
        (int)spell_target->query_prop(OBJ_I_INVIS) - 1);

    if (!spell_target->query_prop(OBJ_I_INVIS))
    {
        spell_target->catch_tell("You become visible again.\n");
    }

    filter(nosee, &check_vis(spell_target))->catch_msg(QCTNAME(spell_target) +
        " appears before you!\n");

    remove_spell_effect_object();

    return 1;
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    dispel_spell_effect(attacker);
}

public void
attack_object(object enemy)
{
    shadow_who->attack_object(enemy);
    dispel_spell_effect(this_player());
}

public void
attacked_by(object enemy)
{
    shadow_who->attacked_by(enemy);
    dispel_spell_effect(enemy);
}

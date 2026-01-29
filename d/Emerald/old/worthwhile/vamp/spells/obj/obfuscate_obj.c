inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>

int invis, invis_on, fade_out_alarm;
object cmds;

varargs public int dispel_spell_effect(object dispeller);
public void warn_dispel();
public void mkcmds();

public int
start()
{
    set_spell_effect_desc("invisibility");

    if (!shadow_me(spell_target))
    {
        return 0;
    }

    invis_on = 1;
    invis = spell_target->query_effective_vamp_stat() / 60 + 1;
    spell_target->add_prop(OBJ_I_INVIS, 
        (int)spell_target->query_prop(OBJ_I_INVIS) + invis);

    set_alarm(itof(1200 + random(500)), 0.0, warn_dispel);

    mkcmds();

    return 1;
}

public void
mkcmds()
{
    setuid();
    seteuid(getuid());
    cmds = clone_object("/d/Emerald/vamp/spells/obj/obfuscate_cmd");
    cmds->set_obfuscate_effect(this_object());
    cmds->move(spell_target, 1);
}

public int
check_vis(object target, object onlooker)
{
    return (CAN_SEE_IN_ROOM(onlooker) &&
        CAN_SEE(onlooker, target));
}

public void
warn_dispel()
{
    if (!spell_target)
    {
        dispel_spell_effect();
        return;
    }

    spell_target->catch_tell("You sense yourself becoming visible again.\n");
    set_alarm(100.0, 0.0, dispel_spell_effect);
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object *nosee;

    if (!spell_target)
    {
        remove_spell_effect_object();
        return 1;
    }

    cmds->remove_object();

    nosee = filter(all_inventory(environment(spell_target)) -
        ({ spell_target }), not @ &check_vis(spell_target));

    if (invis_on)
    {
        spell_target->add_prop(OBJ_I_INVIS,
            (int)spell_target->query_prop(OBJ_I_INVIS) - invis);

        if (!spell_target->query_prop(OBJ_I_INVIS))
        {
            spell_target->catch_tell("You become visible again.\n");
        }

        filter(nosee, &check_vis(spell_target))->catch_msg(QCTNAME(spell_target) +
            " appears before you!\n");
    }

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

public int
query_invis_on()
{
    return invis_on;
}

public void
fade_out()
{
    if (get_alarm(fade_out_alarm))
    {
        remove_alarm(fade_out_alarm);
    }

    fade_out_alarm = 0;
    invis_on = 1;
    spell_target->add_prop(OBJ_I_INVIS,
        (int)spell_target->query_prop(OBJ_I_INVIS) + invis);
    spell_target->catch_tell("You fade out of view.\n");
}

public void
fade_in()
{
    invis_on = 0;
    spell_target->add_prop(OBJ_I_INVIS,
        (int)spell_target->query_prop(OBJ_I_INVIS) - invis);
    spell_target->catch_tell("You fade into view.\n");

    if (random(100) >= 5)
    {
        fade_out_alarm = set_alarm(
            itof(spell_target->query_effective_vamp_stat() /(30 + random(20))),
            0.0, fade_out);
    }
    else
    {
        dispel_spell_effect();
    }
}

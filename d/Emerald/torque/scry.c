inherit "/d/Genesis/newmagic/spell";

#include "torque.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#define DEBUG_ON
#undef  DEBUG_ON

#ifndef DEBUG_ON
#  define MIN_INTERVAL    120
#else
#  define MIN_INTERVAL   0
#endif DEBUG_ON

#define FAILURE_CHARGE 8
#define SUCCESS_CHARGE 18

public object *target_torque(object caster, string arg);
public int scry_resist(object caster, object target, int element, int difficulty);

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("scry");
#ifdef DEBUG_ON
    set_spell_time(1);
#else
    set_spell_time(10);
#endif DEBUG_ON
    set_spell_target(target_torque);
    set_spell_mana(80);
    set_spell_task((TASK_ROUTINE + TASK_SIMPLE) / 2);
    set_spell_element(SS_ELEMENT_AIR, 25);
    set_spell_form(SS_FORM_DIVINATION, 0);
    set_spell_resist(scry_resist);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_visual(1);
    set_spell_vocal(0);
    
    return 0;
}

public object
get_torque(object caster)
{
    object *torques;

    setuid();
    seteuid(getuid());

    torques = TORQUE_MANAGER->get_active_torques();
    torques = filter(torques, &operator(==)(caster->query_real_name()) @
                              &->query_bound());
    if (sizeof(torques) > 1)
    {
        // Multiple torques are bound...should probably log this....
        return 0;
    }

    return torques[0];
}

public int
concentrate_spell(object caster, object *targets, string arg)
{
    object torque = get_torque(caster);

    if (!torque)
    {
        return 1;
    }

    if (!torque->add_charge(FAILURE_CHARGE))
    {
        return 1;
    }

    return ::concentrate_spell(caster, targets, arg);
}

public object *
target_torque(object caster, string str)
{
    mixed *oblist;
    object *torques;

    torques = TORQUE_MANAGER->get_active_torques(this_object());
    if (!parse_command(str, torques, "[the] %i", oblist))
    {
        caster->catch_tell("No such torque.\n");
        return ({});
    }

    if ((oblist[0] <= 0) && (sizeof(oblist) > 2))
    {
        caster->catch_tell("Please be more specific.\n");
        return ({});
    }

    return ({ oblist[oblist[0]] });
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object env, owner, this_torque, target_torque, *items, *dead, *live;
    string tmp;


    if (!(this_torque = get_torque(caster)))
    {
        return;
    }

    target_torque = targets[0];
    env = (target_torque ? environment(target_torque) : 0);
    if (env && living(env))
    {
        owner = env;
#ifndef DEBUG_ON
        if (owner->query_wiz_level())
        {
            caster->catch_tell("You can't seem to locate the person"
                             + " whom you are trying to scry.\n");
            return;
        }
#endif

        env = environment(owner);
    }

    if (!env ||
        !target_torque->query_torque_active(this_object()) ||
        env->query_no_snoop() ||
        env->query_prevent_snoop() ||
        env->query_prop(ROOM_M_NO_MAGIC) ||
        owner->query_prop(OBJ_M_NO_MAGIC))
    {
        caster->catch_tell("For some reason, you were unable to scry " +
            "your target.\n");
        return;
    }

    if ((time() - this_torque->query_last_scry_time()) < MIN_INTERVAL)
    {
        caster->catch_tell("No vision appears.\n");
        return;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("No vision appears.\n");
        this_torque->set_last_scry_time(time() - MIN_INTERVAL / 2 * 3);
        return;
    }     

#ifndef DEBUG_ON
    if (!this_torque->add_charge(SUCCESS_CHARGE))
    {
        return 0;
    }

    owner->add_prop("_player_s_last_scried_by", this_player()->query_real_name());
  
    this_torque->set_last_scry_time(time());
#endif

    owner->catch_tell("The gemstones of your torque burn with a " +
        "sudden heat.\n");

    target_torque->scry(caster, result);
}

public int
query_casting_success(object caster)
{
    return max(0, caster->resolve_task(gSpell_task, ({
        SKILL_WEIGHT, 70, gElement_skill,
        SKILL_WEIGHT, 70, gForm_skill,
        SKILL_WEIGHT, 20, TS_INT,
        SKILL_WEIGHT, 20, TS_WIS,
        SKILL_WEIGHT, 20, TS_DIS, })));
}

public int
scry_resist(object caster, object target, int element, int difficulty)
{
    object wearer;

    if ((wearer = target->query_worn()) &&
        (wearer->query_real_name() == target->query_bound()))
    {
        return spell_resist(caster, wearer, element, difficulty);
    }
    else
    {
        return ::spell_resist(caster, target, element, difficulty);
    }
}

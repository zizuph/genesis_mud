/*
 * /d/Gondor/common/guild2/spells/obj/gostangwedh.c
 *
 * It is used with the 'gostangwedh' spell of the Morgul Mages.
 *
 * Olorin, 08-nov-1995
 * Revision history:
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

int     time = 30,
        strength = -100,
        alarm_id;
object  target;
string  caster;

void
create_object()
{
    set_name(({"gostangwedh", "chains of terror", "chains", }));
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    set_no_show();
}

void
set_up_effect(object victim, int dur, int str)
{
    if (objectp(victim) && living(victim))
        target = victim;
    if (dur > 30)
        time = dur;
    if (str < 0)
        strength = str;

    caster = previous_object()->query_name();
}

void
end_effect()
{
    int     diff;

    diff = target->query_prop(LIVE_I_QUICKNESS) - strength;

    if (diff)
        target->add_prop(LIVE_I_QUICKNESS, diff);
    else
        target->remove_prop(LIVE_I_QUICKNESS);

    strength = 0;
    target->catch_msg("You feel yourself moving faster again.\n");

    set_alarm(0.0, 0.0, remove_object);
}

void
start_effect()
{
    int     old = target->query_prop(LIVE_I_QUICKNESS);

    target->add_prop(LIVE_I_QUICKNESS, old + strength);
    target->catch_msg("You feel yourself moving more slowly.\n");

    alarm_id = set_alarm(itof(time), 0.0, end_effect);
}

void
init()
{
    ::init();

    if (ENV(TO) != target)
        set_alarm(0.0, 0.0, remove_object);

    start_effect();
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (strength)
        end_effect();
}

string
stat_object()
{
    string  str = ::stat_object();

    str += "Time left:\t" + ftoi(get_alarm(alarm_id)[2]) + "\n";
    str += "Strength:\t" + strength + "\n";
    str += "Spell cast by " + caster + ".\n";

    return str;
}


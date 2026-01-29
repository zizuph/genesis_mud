// To be included in everyone on Team Good that will actively engage Team
// Evil in combat

#include "defs.h"

inherit STD_DIR + "good_npc";
inherit LIB_DIR + "grid";

int
query_good_fighter()
{
    return 1;
}

void
notify_attacked(object victim, object enemy)
{
    ::notify_attacked(victim, enemy);
    if (query_attack() || !SEEN(victim, TO) || !SEEN(enemy, TO))
        return;
    if (victim->query_good())
        command("$kill " + OB_NAME(enemy));
    else if (enemy->query_good())
        command("$kill " + OB_NAME(enemy));
}

void
help_called(object room)
{
    string dir;

    if (query_attack())
        return;

    dir = query_grid_direction(E(TO), room);

    if (dir)
        set_alarm(0.0, 0.0, &command("$" + dir));
}

void
shout_for_help()
{
    if (call_for_help())
        command("shout Attackers!");
}

void
attack(object enemy)
{
    command("$kill " + OB_NAME(enemy));
}

void
defend(object victim)
{
    command("$kill " + OB_NAME(victim->query_attack()));
    if (call_for_help())
        command("$shout End this!");
}

int sort_average_stat(mixed a, mixed b)
{
    int a_average = a->query_average_stat(),
        b_average = b->query_average_stat();

    return a_average - b_average;
}

void
enter_env(object to, object from)
{
    object enemy, target, *victims = ({});
    ::enter_env(to, from);
    foreach (object npc: filter(LIVE(E(TO)), &->query_good()))
    {
        if (target = npc->query_attack())
        {
            victims += ({npc});
            if (SEEN(target, TO))
                add_known_enemy(target);
        }
    }

    if (sizeof(victims))
    {
        sort_array(victims, sort_average_stat);
        set_alarm(0.0, 0.0, &defend(victims[0]));
    }
}

void
encounter_living(object o)
{
    ::encounter_living(o);
    if (o->query_prop(LIVE_I_UNDEAD) || query_known_enemy(o))
        attack(o);
}

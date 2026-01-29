/* This file be inherited by all NPCs on 'Team Good' in Raumdor */

#include "defs.h"

// Seconds between calls for help in a given room
#define CALL_LIMIT 30

// Seconds between describing enemies to others
#define DESCRIBE_LIMIT 10

inherit STD_DIR + "npc";

int last_described = 0;

int
query_good()
{
    return 1;
}

int
add_known_enemy(mixed enemy)
{
    int new = 0;
    object *known = query_prop(LIVE_AO_KNOWN_ENEMY);
    if (!known)
        known = ({});
    if (enemy && !pointerp(enemy))
        enemy = ({enemy});
    foreach (object o: enemy)
    {
        if (member_array(o, known) < 0)
        {
            known += ({o});
            new++;
        }
    }
    add_prop(LIVE_AO_KNOWN_ENEMY, known);
    return new;
}

int
query_known_enemy(object enemy)
{
    if (member_array(enemy, query_prop(LIVE_AO_KNOWN_ENEMY)) < 0)
        return 0;
    return 1;
}

int
call_for_help()
{
    int now = time();
    object *rooms;

    if (E(TO)->query_prop(ROOM_I_HELP_CALLED) + CALL_LIMIT > now ||
        TO->query_prop(LIVE_M_MOUTH_BLOCKED))
       return 0;
    E(TO)->add_prop(ROOM_I_HELP_CALLED, now);
    rooms = FIND_NEIGHBOURS(E(TO), 1);
    foreach (object room: rooms)
    {
        filter(LIVE(room), &->query_good_fighter())->help_called(E(TO));
    }
    return 1;
}

void
shout_for_help()
{
    if (call_for_help())
        command("$shout Help!!!");
}

void
notify_attacked(object victim, object enemy)
{
    if (!SEEN(victim, TO) || !SEEN(enemy, TO))
        return;
    if (victim->query_good())
        add_known_enemy(enemy);
    else if (enemy->query_good())
        add_known_enemy(victim);
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    if (SEEN(enemy, TO))
        add_known_enemy(enemy);
    (LIVE(E(TO)) - ({TO}))->notify_attacked(TO, enemy);
    set_alarm(0.0, 0.0, &shout_for_help());
}

void
describe_enemies()
{
    int described = 0, now = time();
    string desc;

    if (query_prop(LIVE_M_MOUTH_BLOCKED) ||
      last_described + DESCRIBE_LIMIT > now)
    {
        set_alarm(itof(DESCRIBE_LIMIT), 0.0, "describe_enemies");
        return;
    }

    foreach (object o: filter(LIVE(E(TO)), &->query_good()))
        described += o->add_known_enemy(query_prop(LIVE_AO_KNOWN_ENEMY));

    if (!described)
        return;

    if (described < 2)
        desc = "a criminal";
    else if (described < 3)
        desc = "a couple of criminals";
    else if (described < 7)
        desc = "a few criminals";
    else
        desc = "several criminals";

    command("emote shares information about " + desc + ".");
}

void
encounter_living(object o)
{
    if (o->query_prop(LIVE_I_UNDEAD))
    {
        if (call_for_help())
            command("$shout The dead are here!");
    }
    else if (query_known_enemy(TP))
    {
        if (call_for_help())
            command("$shout Criminal!!!");
    }
    else if (o->query_good())
    {
        set_alarm(1.0, 0.0, &describe_enemies());
    } 
}

void
notify_change_invis(object ob)
{
    if (SEEN(ob, TO))
        encounter_living(ob);
}

void
init_living()
{
    ::init_living();
    if (SEEN(TP, TO))
        set_alarm(0.0, 0.0, &encounter_living(TP));
}

/*
 * road_messages.c
 *
 * A little module that sends random messages into
 * occupied road rooms in port macdunn.
 *
 * Khail - July 22, 1997
 */
#pragma strict_types
#pragma no_clone

#include "room.h"

inherit "/std/object";

int m_alarm;

public void give_message();

public void
start_messages()
{
    if (get_alarm(m_alarm))
        return;
    m_alarm = set_alarm(10.0 + itof(random(10)), 0.0, give_message);
}

public void
stop_messages()
{
    remove_alarm(m_alarm);
}

public int
filter_to_hear(object ob)
{
    return environment(ob)->is_port_macdunn_road();
}

public string
random_message()
{
    int val;

    val = random(8);

    if (!val)
        return "You hear some shouting in the distance, " +
            "followed by boisterous laughter.\n";
    if (val == 1)
        return "Some children rush through the room, " +
            "and disappear around a corner with a great " +
            "deal of giggling.\n";
    if (val == 2)
        return "A loud crash followed by rather colourful " +
            "swearing comes from somewhere else in the " +
            "village.\n";
    if (val == 3)
        return "A man, wide-eyed with panic, charges past " +
            "as fast as his legs can carry him. Immediately " +
            "behind him a rather large woman wielding a " +
            "rolling pin races after him screaming obscenities.\n";
    if (val == 4)
        return "A handful of chickens wander across the road, " +
            "and scatter with a great deal of clucking at " +
            "your presence.\n";
    if (val == 5)
        return "A group of villagers hustle past you, busily " +
            "on their way someplace. Where, you have no idea, " +
            "this doesn't really look like the sort of place " +
            "where anything has to be done in a certain " +
            "time limit.\n";
    if (val == 6)
        return "You hear the clatter of steel and someone " +
            "shouting 'Goblins!' from down a road, followed " +
            "closely by accusations of too much whiskey " +
            "at Murah's.\n";
    if (val == 7)
        return "Hearing a piercing cry from above, you " +
            "look up to see a few seagulls wheeling about " +
            "high in the sky.\n";
    return "";
}
    
public void
give_message()
{
    object *players;

    players = filter(users(), filter_to_hear);

    if (!sizeof(players))
    {
        stop_messages();
        return;
    }

    players->catch_tell(random_message());
    m_alarm = set_alarm(120.0 + itof(random(120)), 0.0, give_message);
}        

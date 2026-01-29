inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

int     delay_id;
string  from_room;

void
create_object()
{
    set_name("Morgul_Naro_Drego_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_from_room(mixed room)
{
    if (objectp(room))
        from_room = file_name(room);
    else if (stringp(room))
        from_room = room;
}

void
check_for_enemy(object mage)
{
    object  tp,
            room,
            liv;

    tp = ENV(TO);
    if (!objectp(tp) || !tp->query_npc() || !objectp(mage))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    room = ENV(tp);
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    if (file_name(room) != from_room)
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    tp->command("kill "+OB_NAME(mage));


    set_alarm(0.0, 0.0, remove_object);
}

mixed *
filter_extensions(string *exits) {
    for(int i = 0; i < sizeof(exits); i++) {
        if (stringp(exits[i])) {
            if (exits[i][-2..] == ".c") {
                exits[i] = exits[i][..-3];
            }
        }
    }

    return exits;
}

void
move_back(object mage)
{
    int     i,
            panic;
    mixed   exits;
    object  tp,
            room,
            enemy;

    delay_id = 0;

    // Sanity checks.
    if (!stringp(from_room))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    tp = ENV(TO);
    if (!objectp(tp) || !tp->query_npc())
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    room = ENV(tp);
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    // Do not run away if in combat!
    if (objectp(enemy = tp->query_attack()) && present(enemy, room))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    // Is the an exit leading back?
    exits = filter_extensions(room->query_exit());
    if ((i = member_array(from_room, exits)) < 0)
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    // Revenge!
    tp->command(exits[i+1]);
    set_alarm(0.0, 0.0, &check_for_enemy(mage));
}

void
move_back_with_delay(object mage, int delay)
{
    if (!stringp(from_room))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    delay_id = set_alarm(itof(delay), 0.0, &move_back(mage));
}


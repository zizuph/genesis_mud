/*
 *  /d/Gondor/minas/doors/suspect_door.c
 *
 *  The doors leading into the houses of the suspects in Minas Tirith
 *
 *  Olorin, 2-jun-1995
 */
#pragma strict_types

inherit "/std/door";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_door()
{
    set_door_name(({"wooden door", "door"}));
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(20 + random(21));
}

public int
do_knock(string str)
{
    object  tp = TP,
            npc;

    if (str != "door" && str != "on door")
        NFN0("Knock on what?");

    if (open_status)
    {
        write("You knock on the open door. Stupid, isn't it?\n");
        say(QCTNAME(tp) + " knocks on the open door. Stupid, isn't it?\n");
        return 1;
    }
    write("You knock on the door.\n");
    say(QCTNAME(tp) + " knocks on the door.\n");
    other_room->load_me();
    tell_room(other_room, "Someone is knocking on the door.\n");

    if (objectp(npc = present("dunadan", find_object(other_room))))
    {
        npc->command("open door");
        npc->command("shout Come in!");
        tell_room(ENV(TO), "A "+npc->query_gender_string()+" "
          + npc->query_race_name() + " voice shouts: Come in!\n");
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(do_knock, "knock");
}

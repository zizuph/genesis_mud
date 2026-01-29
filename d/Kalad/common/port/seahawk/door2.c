inherit "/std/door";
#include "../default.h"

void
create_door()
{
    set_door_id("jaildoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"iron-barred door","door"}));
    set_other_room(PORT + "seahawk/ba6");
    set_door_desc("A barred jail door.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_pick(20);
    set_key(3);
}

/*
* Someone is trying to pick the lock, well, if the trap is there it will
   * go off!
*/
void
do_pick_lock(int skill, int pick)
{
    object room;

    ::do_pick_lock(skill, pick);

    room = environment(this_object());
    if (room->query_trap())
	room->do_trap(this_player());
}


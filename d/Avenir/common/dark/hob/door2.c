/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/door";
#include "hob.h"

public void
create_door(void)
{
    set_door_id("dark:hobgobbo:door1");
    set_other_room(HOB + "entrance");
    set_door_name(({"white door", "door",}));
    set_pass_command(({"s", "south", "exit", "out"}));

    set_door_desc("A silver-white door inscribed with a cresent moon " +
	"leads out of the tower. The door is wood and metal.\n");

    set_closed_desc("A silver-white door is set into the south wall.\n");

    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

    set_open(0);
    set_locked(1);
//  Do not set this!
//  Players may get stuck.
//    set_key(HOBS_KEY);
    set_no_pick();
}

private int close_alarm;

public void
auto_close(void)
{
    close_alarm = 0;

    if (!open_status)
	return;

    do_close_door("The "+ short() +" swings closed of its own accord.\n");
    do_lock_door("The lock on the "+ short() +" latches shut.\n");

    other_door->auto_close();
}

public void
do_open_door(string mess)
{
    ::do_open_door(mess);

    if (!close_alarm)
	close_alarm = set_alarm(itof(5 + random(6)), 0.0, auto_close);
}

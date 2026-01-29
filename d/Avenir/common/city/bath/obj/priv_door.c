/*
 * ~/priv_door.c
 *
 * Door to a private room in the baths.
 *
 * Revisions:
 *   Lilith, Feb 2002: Created
 *   Lucius, Oct 2005: Updated door messages..
 *   Lucius, Aug 2016: Recoded baths.
 *   Zizuph, Oct 2022: Block players with intimate off from entering baths.
 *
 */
#pragma strict_types
inherit "/std/door";
#include "../bath.h"
#include <options.h>

// 5 Minutes
#define ALARM_IVAL	300.0

private int extern, alarm_id;
private mapping exit_dirs = ([
    "n"  : ({ "n",  "north" }),
    "s"  : ({ "s",  "south" }),
    "e"  : ({ "e",  "east"  }),
    "w"  : ({ "w",  "west"  }),
    "sw" : ({ "sw", "southwest" }),
    "nw" : ({ "nw", "northwest" }),
    "se" : ({ "se", "southeast" }),
    "ne" : ({ "ne", "northeast" }),
]);
/*
 * We only lock the outside door, never the inside door
 * to avoid possible hostage situations.
 */
public void
config_door(string room, string other, string dir)
{
    set_pass_command(exit_dirs[dir]);
    set_other_room(BATHRM + other);
    set_door_name(({ "door", room }));

    set_short("door to room "+ room);
    set_door_desc("This is the door to Private Room "+
	capitalize(room) +".\n");

    if (wildmatch("*priv_*", other))
    {
	extern = 1;
	set_key(random(10000) * -1);
    }
}

public void
create_door(void)
{
    set_door_id(PRIV_DOOR_ID);

    set_open(0);
    set_locked(1);
    set_no_pick();

    set_open_desc("");
    set_closed_desc("");

    set_lock_command("lock");
    set_unlock_command("unlock");

    set_no_show_composite(1);
}

/*
 * Auto-close any doors left open
 * longer than 5 minutes.
 */
public void
auto_close(int lock)
{
    if (query_open())
    {
	do_close_door("The "+ short() +" swings closed and locks.\n");
	other_door->do_close_door("The "+ other_door->short() +
	    " swings closed and locks.\n");
    }

    if (lock)
    {
	set_locked(1);
	other_door->set_locked(1);
    }
}

public void
do_close_door(string mess)
{
    if (alarm_id)
    {
	remove_alarm(alarm_id);
	alarm_id = 0;
    }

    ::do_close_door(mess);
}

public void
do_open_door(string mess)
{
    /*
     * Only trigger from the inside
     * so we don't have two alarms
     * trying to do the same thing.
     */
    if (!extern && !alarm_id)
	alarm_id = set_alarm(ALARM_IVAL, 0.0, &auto_close(1));

    ::do_open_door(mess);
}

int
pass_door(string arg)
{
    if (this_player()->query_option(OPT_BLOCK_INTIMATE) &&
        !this_player()->query_wiz_level())
    {
        write("You decide against entering into the private bath.\n");
        return 1;
    }
    return ::pass_door(arg);
}

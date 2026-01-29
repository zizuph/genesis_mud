inherit "/std/door";
#include <macros.h>
#include "../defs.h"

void
reset_door()
{
    tell_room(G_ROOMS + "dungeon", BS("A guard strolls in, looks in " +
        "the cell for a moment, then closes and locks the door.  He " +
        "then leaves.\n"));
    TO->set_locked(1);
    TO->set_open(0);
}

create_door()
{
    set_door_id("cdoor");
    set_pass_command(({"s", "south"}));
    set_door_name(({"iron door", "door"}));
    set_door_desc(break_string(
"This is a door made of solid iron.  It looks very heavy, and impossible to " +
"force open.  There is one tiny window in the center of the door, at about " +
"eyelevel.\n", 78));
    set_other_room(G_ROOMS + "cell");
    set_open(0);
    set_locked(1);
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_pick(10);
    set_lock_desc(break_string(
"The lock looks really easy to pick...\n", 78));
    set_key("cell_door_key");
    reset_door();
}

void
init()
{
    ::init();
    add_action("knock", "knock");
}

int
knock(string arg)
{
    notify_fail("Knock on what?\n");
    if (!arg) 
        return 0;
    if (arg != "door" && arg != "iron door" && arg != 
        "on door" && arg != "on iron door")
        return 0;
        write("You knock on the door.\n");
        say(QCTNAME(this_player()) + " knocks on the door.\n");
        return 1;
}




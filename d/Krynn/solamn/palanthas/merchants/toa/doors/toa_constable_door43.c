/*
 * Fourth floor outside door to the Constable's rooms in the Tower of Arms in
 * Palanthas.
 * Solid lock. Key exists.
 * 
 * Mortis 09.2014
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../../../local.h"

inherit "/std/door";

#define OSIDE                (TOA + "toa67")

int door_alarm = 0;

/* Prototypes */
string relock_door();

void
reset_door()
{
    if (TO->query_open() == 1)
    {
        TO->close_door("door");
    }
    if (TO->query_locked() == 0)
    {
        TO->set_locked(1);
        tell_room(E(TO), "The door whirs and clicks.\n");
        object otarget = find_object(OSIDE);
        otarget->auto_door();
    }
}

void
create_door()
{
    set_door_desc("This bolted, iron door leads west into the marble wall. "
    + "It has a burnished iron handle with a small keyhole.\n");
    set_door_id("toa_constable_door");
    set_pass_command(({"west","in", "door"}));
    set_door_name(({"door"}));
    set_other_room(TOA + "toa67.c");
    set_open(0);
    set_fail_pass("You must first open the door before you will be able "
    + "to use it effectively.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"turns the burnished iron handle and opens the iron "
    + "door.\n", "The iron door opens.\n"}));
    set_fail_open(({"The door is already open.\n", "The door is "
    + "locked and will not budge.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pushes the iron door closed.\n", "The iron door "
    + "closes.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is set into a keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the iron door.\n", "A loud 'click' is heard " +
        "as the iron door is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"@@relock_door", "A loud 'click' is " + 
        "heard as the iron door is unlocked.\n"}));
    set_fail_unlock("But the iron door is already unlocked.\n");
    set_key("toa_constable_door");
    set_pick(69);
    set_lock_name("toa_constable_door");
}

string
relock_door()
{
    remove_alarm(door_alarm);
    door_alarm = set_alarm(60.0, 0.0, &reset_door());
    return "unlocks the iron door.\n";
}

/*
 * Function name: do_pick_lock
 * Description:   Here we pick the lock, redefine this function if you want
 *                something to happen, like a trap or something,
 *                and what we want to happen is the auto-lock function.
 * Arguments:     skill - randomized picking skill of player
 *                pick  - how difficult to pick the lock
 */
void
do_pick_lock(int skill, int pick)
{
    if (skill > pick)
    {
        if (no_pick)
        {
            write("You failed to pick the lock. It's too hard for someone "
            + "with your skills.\n");
            E(TO)->defend_door(TP);
            return;
        }

        write("You get very satisfied when you hear a soft 'klick' from " +
            "the lock.\n");
        say("You hear a soft 'klick' from the lock.\n");
        do_unlock_door("");
        other_door->do_unlock_door(check_call(unlock_mess[1]));
        remove_alarm(door_alarm);
        door_alarm = set_alarm(60.0, 0.0, &reset_door());
    }
    else if (skill < (pick - 50))
    {
        write("You failed to pick the lock. It seems unpickable to you.\n");
        E(TO)->defend_door(TP);
    }
    else
    {
        write("You failed to pick the lock.\n");
        E(TO)->defend_door(TP);
    }
}

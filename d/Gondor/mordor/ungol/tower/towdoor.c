/*
 * The standard door in the the tower at Citith Ungol.
 */

inherit "/std/door";

#include "/d/Gondor/defs.h"

#define PICK_LEVEL 40
#define STANDARD_TOWER_KEY 15688453

void
create_door()
{
    set_open_command("open");
    set_close_command("close");
    set_lock_command("lock");
    set_unlock_command("unlock");

    set_open(0);
    set_locked(1);
    set_pick(PICK_LEVEL);

    add_item( ({ "band", "bands" }), BSN("The metal bands are fastened to " +
        "the door to make it stronger than it is already."));
    add_item("oak", BSN("The door is made of solid oak, which makes " +
        "the door very strong. It looks much too tough to bash."));

    set_lock_name( ({ "iron lock", "lock" }) );
    set_lock_desc(BSN("The lock looks very strong. It is made of iron and " +
        "you don't think that you can open the lock without a key."));

    set_key(STANDARD_TOWER_KEY);
}

string
get_opposite_direction(string direction)
{
    switch(direction)
    {
        case "north"    : return "south";
        case "south"    : return "north";
        case "west"     : return "east";
        case "east"     : return "west";

        case "northwest": return "southeast";
        case "northeast": return "southwest";
        case "southwest": return "northeast";
        case "southeast": return "northwest";
    }

    return "stone"; /* should never happen */
}

void
make_the_door(string other_room, string direction)
{
    string opposite = get_opposite_direction(direction);

    set_other_room(other_room);
    set_door_id(other_room + " " + direction);
    set_door_name( ({ direction + " door" , "door" }) );
    set_open_desc(BSN("The door in the " + direction + " wall is made of " +
        "solid oak. It is secured with iron bands. It looks very strong. " +
        "Throught the opened door, you can see a dimly lit room. You cannot " +
        "see any details in the adjacent room though."));
    set_close_desc(BSN("The door in the " + direction + " wall is made of " +
        "solid oak. It is secured with iron bands. It looks very strong and " +
        "you do not think that you can open it by force. The door is " +
        "closed."));
    set_pass_command( ({direction, direction[0]}) );
    set_fail_pass("As you try to walk " + direction + ", you bump against " +
        "a strong oak door.");
    set_open_mess( ({
        "opens the oak door in the " + direction + " wall.",
        BSN("Suddenly the oak door in the " + opposite + " wall opens.") }) );
    set_fail_open( ({
        BSN("The oak door in the " + direction + " wall is already open."),
        BSN("The oak door in the " + direction + " wall is locked.") }) );
    set_close_mess( ({ "closes the oak door to the " + direction + ".",
        BSN("Suddenly the oak door in the " + opposite + " wall closes.") }) );
    set_lock_mess( ({
        "locks the oak door to the " + direction + ".",
        BSN("Suddenly you hear a sound as if the oak door in the " + opposite +
            " wall is being locked.") }) );
    set_unlock_mess( ({
        "unlocks the oak door to the " + direction + ".",
        BSN("Suddenly you hear a sound as if the oak door in the " + opposite +
            " wall is being unlocked.") }) );
    set_fail_lock( ({
        BSN("The oak door in the " + direction + " wall is already locked.") ,
        BSN("The oak door in the " + direction + " wall cannot be locked " +
            "for it is open.") }) );
    set_fail_close(BSN("The oak door in the " + direction + " wall is " +
        "already closed."));
    set_fail_unlock(BSN("The oak door in the " + direction + " is not " +
        "locked."));
}


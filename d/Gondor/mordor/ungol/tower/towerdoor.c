/*
 * /d/Gondor/mordor/ungol/tower/towerdoor.c
 *
 * The standard door in the the tower at Citith Ungol. It can have to different
 * locks.
 *
 * /Mercade, 23 September 1993
 *
 * Revision history:
 */

inherit "/std/door";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/mordor/ungol/tower/tower.h"

/*
 * Global variable
 */
int door_number = 0; /* the type of the key (not the number) */

/*
 * Called to create the door.
 */
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

    add_item( ({ "band", "bands" }),
        BSN("The metal bands are fastened to the door to make it stronger " +
        "than it already is."));
    add_item("oak",
        BSN("The door is made of solid oak, which makes the door very " +
        "strong. It looks much too tough to bash."));

    set_lock_name( ({ "iron lock", "lock" }) );
    set_lock_desc(BSN("The lock looks very strong. It is made of iron and " +
        "you don't think that you can open the lock without a key."));
}

/*
 * Get the direction opposite to a certain direction.
 */
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

        case "down"     : return "up";
        case "up"       : return "down";

        case "in"       : return "out";
        case "out"      : return "in";
    }

    return "stone"; /* should never happen */
}

/*
 * Make an array of pass commands from the direction.
 */
string *
get_pass_commands(string direction)
{
    switch(direction)
    {
        case "north"    : return ({ "north", "n" });
        case "south"    : return ({ "south", "s" });
        case "west"     : return ({ "west",  "w" });
        case "east"     : return ({ "east",  "e" });

        case "northwest": return ({ "northwest", "nw" });
        case "northeast": return ({ "northeast", "ne" });
        case "southwest": return ({ "southwest", "sw" });
        case "southeast": return ({ "southeast", "se" });

        case "down"     : return ({ "down", "d" });
        case "up"       : return ({ "up",   "u" });

        case "in"       : return ({ "in" });
        case "out"      : return ({ "out" });
    }

    return ({ direction }); /* should never happen */
}

/*
 * Called to make the door itself.
 */
void
make_the_door(string door_id_string, string other_room, string direction,
    int key_number)
{
    string opposite = get_opposite_direction(direction);

    set_other_room(other_room);
    set_door_id(door_id_string);
    set_door_name( ({ direction + " door" , "door", "oak door" }) );
    set_open_desc(BSN("An open oak door, leading " + direction + "."));
    set_closed_desc(BSN("A closed oak door, leading " + direction + "."));
    set_door_desc(BSN("The door in the " + direction + " wall is made of " +
        "solid oak. It is secured with iron bands. It looks very strong."));
    set_pass_command(get_pass_commands(direction));
    set_fail_pass(BSN("As you try to walk " + direction + ", you bump " +
        "against a strong oak door."));
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
    set_fail_unlock(BSN("The oak door in the " + direction + " wall is not " +
        "locked."));

    door_number = key_number;
    if (key_number == 1)
    {
        set_key(TOWER_KEY_NUMBER_1);
    }
    else
    {
        set_key(TOWER_KEY_NUMBER_2);
    }
}

/*
 * You can query the number of the type of the key of this door with this
 * function. Note that this isn't the key number (code).
 */
int
query_number()
{
    return door_number;
}

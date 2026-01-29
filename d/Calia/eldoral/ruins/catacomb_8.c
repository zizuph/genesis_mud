/*
 * catacomb_8.c
 *
 * A fairly typical room, except for the door to the south. A handle
 * on the wall may be pulled to open the door from this side.
 *
 * Khail - Feb 12/97
 */
#pragma strict_types

#include "defs.h"

inherit STDROOM;

int door_open;

/*
 * Function name: check_pass
 * Description  : VBFC'd exit blocking function. Prevents players
 *                from using this exit until the south 'door' is
 *                opened.
 * Arguments    : n/a
 * Returns      : 0 - Player may pass.
 *                1 - Player can't pass.
 */
public int
check_pass()
{
    if (!door_open)
    {
        write("You cannot pass through solid stone!\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: check_vis
 * Description  : VBFC'd exit visibility function. Prevents players
 *                from seeing a south exit until the 'door' is
 *                opened.
 * Arguments    : n/a
 * Returns      : 1 - Exit invis.
 *                0 - Exit vis.
 */
public int
check_vis()
{
    return !door_open;
}

/*
 * Function name: exa_door
 * Description  : VBFC'd add_item desc for the door.
 * Arguments    : n/a
 * Returns      : A string describing the door.
 */
public string
exa_door()
{
    if (!door_open)
        return "The simple stone slab is quite plain, but " +
            "effectively prevents further passage to " +
            "the south.\n";
    else
        return "The door has withdrawn almost completely into " +
            "the wall, opening the way south into a dark " +
            "passage.\n";
}

/*
 * Function name: create_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("catacombs beneath " + CASTLE_NAME);
    set_long("You are in a narrow passage somewhere in the " +
        "catacombs beneath " + CASTLE_NAME + ". This dark passage appears " +
        "to have been carved out from solid stone rather than " +
        "excavated and built up with blocks. The walls, floor " +
        "and ceiling are perfectly smooth, if not damp and " +
        "covered in a rather slimy mixture of water and dust. It leads " +
        "off to the south, and a narrow, spiral stone stairway " +
        "descends downwards from this point.\n\n");

    add_item(({"ceiling", "roof"}),
        "Carved from the surrounding stone, it slops steeply down " +
        "the curving stairway.\n");
    add_item(({"floor", "ground", "steps"}),
        "The steps have also been cut from solid stone, but " +
        "fortunately they've been left rough, there should be " +
        "little, if any, chance for slipping on them.\n");
    add_item(({"mixture"}),
        "The walls and steps are slicked by a somewhat slimey " +
        "mixture formed of dusty silt and water. It's not pretty, " +
        "but at least it's not dangerous, either.\n");
    add_item(({"wall", "walls"}),
        "The walls are quite plain, and appear to have been " +
        "carved from the surrounding stone rather than assembled " +
        "from blocks. Your attention is drawn to a lever of some " +
        "sort embedded into the wall near the door, however.\n");
    add_item(({"lever", "handle"}),
        "It's a simple stone shaft, about the length of your " +
        "forearm, jutting out of the wall.\n");
    add_item(({"door", "slab", "doorway"}),
        VBFC_ME("exa_door"));

    DARK;
    INSIDE;

    add_exit(RUIN + "catacomb_4", "south", VBFC_ME("check_pass"),
        1, VBFC_ME("check_vis"));
    add_exit(GROTTO + "bot_stairs", "down");
}

/*
 * Function name: close_the_door
 * Description  : Closes the passage to the south.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
close_the_door()
{
    if (door_open)
    {
        tell_room(TO, "A stone door slides back into place, " +
            "closing off the passage to the south.\n");
        door_open = 0;
    }
}
     
/*
 * Function name: open_the_door
 * Description  : Opens up the passage to the south.
 * Arguments    : second - Optional arg called when the door is
 *                         opened from the other side.
 * Returns      : n/a
 */
public varargs void
open_the_door(int second = 0)
{
    seteuid(getuid());

    if (!door_open)
    {
        tell_room(TO, "Suddenly, the door blocking the way " +
            "south begins rumbling to one side, opening the " +
            "way into a dark passage beyond.\n");
        door_open = 1;
    }
    if (!second)
    {
        (RUIN + "catacomb_4")->open_the_door(1);
    }
}

/*
 * Function name: do_open
 * Description  : Allows players to attempt to open the door.
 * Arguments    : str - String passed as argument to the command
 *                      verb.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_open(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (str != "handle" && str != "lever")
        return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NF("It's too dark to see.\n");
        return 0;
    }

    write("You fiddle with the lever for a moment, and finally " +
        "feel something give on the other side of it.\n");
    say(QCTNAME(TP) + " fiddles with the lever for a moment, " +
        "and it finally seems to move somewhat.\n");
    if (door_open)
    {
        tell_room(TO, "It doesn't seem to have any effect, however.\n");
        return 1;
    }
    open_the_door();
    return 1;
}
     
/*
 * Function name: init
 * Description  : Initializes commands when objects meet.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_open, "pull");
    add_action(do_open, "move");
}
 
public void
reset_room()
{
    close_the_door();
}



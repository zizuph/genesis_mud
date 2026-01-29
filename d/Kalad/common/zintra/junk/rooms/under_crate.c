inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

int trapdoor;

void
create_room()
{
    set_short("Under Crate");
    set_long( break_string(
"You are in a very dark passage underneath a warehouse.  The walls are " +
"smooth, and non-descript.  The passage ends here and continues to the " +
"north.  There is a ladder affixed to the south wall, and it ends at the " +
"ceiling.  " + "@@add_desc@@", 78));

    add_exit(G_ROOMS + "passage", "north", "@@trap_fun");

    add_item("ladder", break_string(
"Its just a plain ladder, but there is a interesting-looking lever next to " +
"it.  Perhaps the lever warrants a closer look?\n", 78));

    add_item("lever", break_string(
"The lever seems to be attached to some sort of mechanism behind the " +
"wall.  This isn't like the 'make-shift' work of the gnomes.  This is " +
"serious, heavy-duty equipment, intended to last a while.  Perhaps the " +
"lever is pullable?\n", 78));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}

void
init()
{
    ::init();
    add_action("pull_lever", "pull");
    add_action("go_up", "u");
    add_action("go_up", "up");
}

string
add_desc()
{
    if (trapdoor)
        return "\nThere is an open trapdoor in the ceiling, right at the " +
               "end of the ladder.\n";
    return "No exit at the top of the ladder is immediately evident.\n";
}

int
trap_fun()
{
    if (trapdoor)
    {
        write ("As you leave, the trapdoor snaps shut.\n");
        say ("As " + QCTNAME(this_player()) + " leaves the room, the " +
            "trapdoor snaps shut.\n");
        trapdoor = 0;
        return 0;
    }
    else return 0;
}

int
pull_lever(string str)
{
    notify_fail("Pull what?\n");
    if (!str && str != "lever") return 0;
    if (trapdoor)
    {
        notify_fail("You pull the lever, but the trapdoor is already open.\n" +
                    "The trapdoor will close automatically when you leave.\n");
        return 0;
     }
    trapdoor = 1;
    write( break_string ("You pull the lever and it snaps back into place." +
          "  A trapdoor opens in the ceiling above you.\n", 78));
    say (QCTNAME(this_player()) + "pulls the lever and a trapdoor opens" +
        " in the ceiling above you.\n");
    return 1;
}

int
go_up(string str)
{
    notify_fail ("Up where?\n");
    if (str) return 0;
    if (!trapdoor) return 0;
    this_player()->move_living(
        "up the ladder and out through the trapdoor, which snaps shut " +
        "immediately afterwards", G_ROOMS + "crate", 1);
    trapdoor = 0;
    return 1;
}

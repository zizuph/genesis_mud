inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

int eopen, wopen;

void
reset_me()
{
    if (eopen = 1 || wopen == 1)
        tell_room(TO, BS("You feel dizzy for a moment.  When you " +
            "recover, things look a little different.\n"));
    eopen = 0;
    wopen = 0;
}

void
create_room()
{
    set_short("Dark Passage");
    set_long(BS(
"This is a long, dark tunnel.  It is almost perfectly round and extends " +
"east-west.  By the reflected light, you notice that the walls seem to " +
"change color about halfway through the tunnel.\n" + "@@extra_desc@@"));

    add_item(({"wall", "walls"}), BS(
"It seems as if you are in some kind of tube.  Upon closer inspection, you " +
"notice that the walls towards the western section of the tunnel are " +
"carved from stone, but towards the east the walls seem to be made " +
"of wood.  How peculiar!\n"));

    add_item(({"north wall", "south wall"}), BS("There really is no 'wall' " +
"there; the passage is tubular in shape.  The walls curve up towards the " +
"ceiling, and down towards the floor.\n"));

    add_item("east wall", "@@east_desc");

    add_item("west wall", "@@west_desc");

    INSIDE
    add_prop(ROOM_I_LIGHT, 0);
}

string
extra_desc()
{
    if (eopen)
    {
    if (wopen) return "There are two obvious exits: east, west.\n";
    return "There is one obvious exit: east.\n";
    }
    if (wopen) return "There is one obvious exit: west.\n";
    return "";
}

string
east_desc()
{
    if (eopen) return "There is no east wall.  Its open.\n";
    return "This wall is made of what appears to be teakwood.  It does not " +
        "look very\nsturdy.\n";
}

string
west_desc()
{
    if (wopen) return "There is no west wall.  Its open.\n";
    return "This wall is made of bricks.  You could push it in easily.\n";
}

void
init()
{
    ::init();
    add_action("push_wall", "push");
    add_action("push_wall", "open");
    add_action("close_wall", "close");
    add_action("move_east", "east");
    add_action("move_east", "e");
    add_action("move_west", "west");
    add_action("move_west", "w");
}

int
close_wall(string str)
{
    if (!str) return 0;
    if (str != "wall" && str != "east wall" && str != "west wall") return 0;
    write ("Funny, you can't seem to find a way to do that from here.\n");
    return 1;
}

int
push_wall(string str)
{
    NF("Push what?\n");
    if (!str) return 0;
    if (str != "wall" && str != "east wall" && str != "west wall") return 0;
    if (str == "wall")
    {
        write ("Which wall do you mean?\n");
        return 1;
    }
    NF("But its already open!\n");
    if (str == "east wall")
    {
        if (eopen) return 0;
        write("You push hard on the east wall.  The entire wall swings " +
            "outward.\n");
        say (QCTNAME(TP) + " pushes on the east wall.  The entire wall " +
            "swings outward.\n");
        call_other(G_ROOMS + "wine_cellar", "open_wall");
        eopen = 1;
        return 1;
    }
    if (str == "west wall")
    {
        if (wopen) return 0;
        write("You push hard on the west wall.  The entire wall swings " +
            "outward.\n");
        say (QCTNAME(TP) + " pushes on the west wall.  The entire wall " +
            "swings outward.\n");
        call_other(G_ROOMS + "cell", "open_wall");
        wopen = 1;
        return 1;
    }
}

int
move_east(string str)
{
    if (str) return 0;
    if (eopen)
    {
        TP->move_living("east", G_ROOMS + "wine_cellar");
        return 1;
    }
    write ("There is no obvious exit east.\n");
    return 1;
}

int
move_west(string str)
{
    if (str) return 0;
    if (wopen)
    {
        TP->move_living("west", G_ROOMS + "cell");
        return 1;
    }
    write ("There is no obvious exit west.\n");
    return 1;
}

void
east_open()
{
    if (eopen)
    {
        tell_room(TO, "Suddenly, the exit to the east vanishes.\n");
        eopen = 0;
        return;
    }
    tell_room(TO, "Suddenly, the east wall swings outward.\n");
    eopen = 1;
}

void
west_open()
{
    if (wopen)
    {
        tell_room(TO, "Suddenly, the exit to the west vanishes.\n");
        wopen = 0;
        return;
    }
    tell_room(TO, "Suddenly, the west wall swings outward.\n");
    wopen = 1;
}

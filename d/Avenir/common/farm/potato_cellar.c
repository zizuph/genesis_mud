#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room.c";
int ladder_down = 0;
int query_ladder();
void drop_ladder();
object tower;
object stairs;

void
create_room()
{
    set_short("The potato cellar");
    set_long("@@desc_long");
    add_item(({"cellar","potato cellar"}),"@@desc_long");
    add_item(({"floor","soil"}),"The floor is just hard stamped " +
        "soil. In one corner you notice two small peculiar " +
        "holes in the ground.\n");
    add_item("corner","There are four corners in the cellar. " +
        "In one of them, there is a huge pile of old rotten " +
        "potatoes piled aganst the wall.\n");
    add_item(({"heap","potatoes","pile"}),"You pick up a " +
        "rotten potato that smells awfully bad and quickly " +
        "drop it back. The potatoes must have been piled here " +
        "many years ago.\n");
    add_item("wall","You touch the wall with your hand. Some " +
        "dirt falls to the floor, but else there is nothing " +
        "particular with them. Ordinary cellar walls.\n");
    add_item("dirt","The whole cellar is covered " +
        "with dirt and soil.\n");
    add_item("ceiling","@@desc_ceiling");
    add_item("holes","@@desc_holes");
    add_item("door","@@desc_door");
    add_item("ladder","@@desc_ladder");
    add_prop(OBJ_I_LIGHT, -1);
    add_prop(ROOM_S_EXIT_FROM_DESC, "from below.");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("east_side","out","@@go_out");
    reset_room();
}

void
reset_room()
{
    (THIS_DIR + "tower")->teleledningsanka();
    (THIS_DIR + "stairs")->teleledningsanka();

    tower = find_object(THIS_DIR + "tower");
    stairs = find_object(THIS_DIR + "stairs");

    if (sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
        return;
    if (sizeof(FILTER_PLAYERS(all_inventory(tower))))
        return;
    if (sizeof(FILTER_PLAYERS(all_inventory(stairs))))
        return;

    remove_exit("up");
    ladder_down = 0;
}

void
init()
{
    ::init();
    add_action("open_door","open");
}

string
desc_door()
{
    string text;

    text = "Its a door that seems to be leading up into " +
        "the house.";
    if (query_ladder())
        text += " You can see a ladder leading up.";
    else
        text += " Right now it is closed, but it seems to " +
            "be easy to open.";
    text += "\n";
    return text;
}

string
desc_holes()
{
    string text;

    text = "You kneel down and examine the small " +
        "holes.";
    if (query_ladder())
        text += " Because the door in the ceiling is open " +
            "and because the ladder is down, standing in " +
            "the two small holes, they make perfect sense. ";
    else
        text += " It's hard to understand what they are " +
            "here for, but it seems something might have stood " +
            "here with some weight placed on it.";
    text += "\n";
    return text;
}

string
desc_long()
{
    string text;

    text = "This is a small cellar used for storing potatoes. " +
        "The floor is made of hard stamped soil and piled in " +
        "a corner is a huge heap of old rotten potatoes.";
    if (query_ladder())
        text += " In another corner you see a ladder leading up " +
            "through a door in the ceiling.";
    text += "\n";
    return text;
}

string
desc_ceiling()
{
    string text;

    text = "You lift your head and watch the " +
        "ceiling. ";
    if (query_ladder())
        text += "In a corner you see an open door " +
            "in the ceiling leading up with the help of " +
            "a ladder.";
    else
        text += "You see some kind of a door in the " +
            "ceiling.";
    text += "\n";
    return text;
}

string
desc_ladder()
{
    string text;

    if (query_ladder())
        text = "Its an ordinary wooden ladder that " +
            "leads up through the open door in the " +
            "ceiling.";
    else
        text = "What?";
    text += "\n";
    return text;
}

int
open_door(string str)
{
    if (strlen(str) && (str == "door"))
    {
        if (query_ladder())
        {
            write("The door is already opened!\n");
            return 1;
    }
        write("You push up the door in the ceiling and " +
            "down tumbles a ladder which allows you to climb " +
            "up.\n");
        say(QCTNAME(TP) + " pushes up a door in the ceiling and " +
            "down tumbles a ladder which allows you to climb " +
            "up.\n");
        ladder_down = 1;
        add_exit("stairs","up");
        return 1;
    }
    return 0;

}

int
go_out()
{
    object east_side;

    east_side = find_object(THIS_DIR + "east_side");
    if (!(east_side->query_door_open()))
    {
        tell_room(east_side, "Suddenly a door in the grass swings " +
            "open.\n");
        east_side->do_open_door();
    }

    return 0;
}

int
query_ladder()
{
    return ladder_down;
}

void
drop_ladder()
{
    ladder_down = 1;
    add_exit("stairs","up");
}

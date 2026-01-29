#include "defs.h"

inherit STDROOM;

public int do_enter(string str);
public int do_jump(string str);

public void
create_room()
{
    set_short("atop an elevated walkway in the north " +
        "parts of the ruins of "+CASTLE_NAME);
    set_long("You are at the northern end of a " +
        "short, elevated walkway in the northern parts " +
        "of the ruins of " + CASTLE_NAME + ". " +
        "Peering cautiously over " +
        "the north edge of the walkway, you can look " +
        "straight down the outside of the northern " +
        "wall of the ruins. " +
        "To the south, you see nothing but " +
        "walls, towers and buildings of various " +
        "parts of the ruins, all in varying stages " +
        "of decay. Below you, to the east, a wide " +
        "courtyard marks the northeast corner of the " +
        "ruins. Beyond the walls of the courtyard " +
        "to the east, and to your north, the forest " +
        "spreads as far as your eye can penetrate " +
        "through the mist that swirls about the " +
        "ruins. On your west side, the remains of a " +
        "tower that collapsed towards the north lie " +
        "like a stone corpse.\n\n");

    add_item(({"sky", "mist"}),
        "The sky is obscured by a thick layer of churning " +
        "white mist.\n");
    add_item(({"ground", "floor"}),
        "The floor of the walkway appears to be made from " +
        "large blocks of stone, possibly also the ceiling " +
        "of a room or tunnel below you.\n");
    add_item(({"staircase", "stairs", "stairway"}),
        "A narrow stone stairway descends beneath the " +
        "surface of the walkway through a small opening " +
        "here.\n");
    add_item(({"opening", "hatchway", "hole"}),
        "It may once have been a hatchway of some sort, " +
        "but time and the elements have claimed any door " +
        "that may have covered it.\n");
    add_item(({"walls"}),
        "All around you spread walls of the ruins, some " +
        "near, some far, but all in various stages of decay " +
        "and eventual collapse.\n");
    add_item(({"buildings", "towers"}),
        "Looking across the ruins to the south, you see " +
        "that most, if not all, of the buildings and towers " +
        "appear to be on the verge of collapse. Already you " +
        "find yourself seeing into rooms where outer walls " +
        "once stood.\n");
    add_item(({"courtyard"}),
        "Below you, to the east, spreads a large, square " +
        "shaped courtyard that makes up the northeast " +
        "part of the ruins. In the heart of the courtyard, " +
        "a number of black pillars stand in a circle. Beyond " +
        "the courtyard outer walls, the forest of the island " +
        "disappears behind and above the ever-thickening mist.\n");
    add_item(({"pillars"}),
        "You can't see much detail from here, but it looks " +
        "like twelve stone pillars, simply cut from some kind " +
        "of black stone.\n");
    add_item(({"forest", "trees"}),
        "Beyond the courtyard, the forest of the island " +
        "spreads out as far as you can see. But considering " +
        "the mist obscures everything more than a stone's " +
        "throw away, that's not very far.\n");
    add_item(({"remains", "tower", "remains of tower"}),
        "To your west, the collapsed remains of a tower form " +
        "an unplanned wall, and extends to the north and south, " +
        "parallel to the walkway. You notice what might " +
        "have been a window at one time is now a gaping " +
        "opening in the side of the tower.\n");
    add_item(({"window", "opening"}),
        "It was probably a window, originally, but now with " +
        "the tower collapsed on its side, it looks more like " +
        "a big hole.\n");

    add_exit(RUIN + "nwalk3", "south");
}

public void
init()
{
    ::init();
    add_action(do_jump, "jump");
    add_action(do_jump, "leap");
    add_action(do_enter, "enter");
    add_action(do_enter, "climb");
}

public int
do_enter(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, TP, 
        "[to] / [into] / [in] / [on] / [onto] / [through] " +
        "[the] 'tower' / 'ledge' / 'window' / 'opening' / 'hole'"))
    {
        write("The opening is too far away for you to " +
            "simply " + query_verb() + " it.\n");
        return 1;
    }
    return 0;
}

public int
do_jump(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, TP, 
        "'to' / 'into' / 'in' / 'on' / 'onto' / 'through' " +
        "[the] 'tower' / 'ledge' / 'window' / 'opening' / 'hole'"))
    {
        write("You take a running start, and clear " +
            "the distance between the wall and the " +
            "opening in the tower quite easily, " +
            "landing fairly roughly on the rubble " +
            "inside.\n");
        say(QCTNAME(TP) + " takes a running start, " +
            "and clears the distance between the wall " +
            "and an opening in the tower quite easily, " +
            "vanishing into the darkness within.\n");
        TP->move_living("M", RUIN + "ntower1", 1, 0);
        say(QCTNAME(TP) + " comes flying through the " +
            "opening in the side of the tower and " +
            "lands in the rubble with a resounding " +
            "thud.\n");
        return 1;
    }
    return 0;
}

public string
tower_desc()
{
    string str;


//  str = ::tower_desc();
    str += "You notice a fair-sized opening in the side " +
        "of the tower, however, that looks to have at " +
        "one time been a ledge. The ledge itself, of " +
        "course, is long gone, but the opening is " +
        "still available for entry into the tower.\n";

    return str;
}
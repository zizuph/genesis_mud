inherit "/d/Emerald/thief_lair/lair_base";

#include "/d/Emerald/defs.h"

#define OTHER_ROOM (THIEF_LAIR_DIR + "cave")

public int
block_west()
{
    write("A cave-in has blocked the tunnel west.\n");
    return 1;
}

public int
block_up()
{
    if (this_player()->query_prop(OBJ_I_WEIGHT) > 90000)
    {
        write("As you step onto the ladder, you notice the ropes tighten, " +
            "barely able to hold your weight.  It is far too dangerous " +
            "to continue up.\n");
        return 1;
    }

    return 0;
}

public void 
create_lair_room()
{
    set_long("   "+
        "You have entered a cave that is very different from the usual " +
        "caves you enter. For starters, the cave looks like it has been " +
        "carved straight out of the solid rock: if you didn't know you " +
        "you were so far underground, you could easily believe you are " +
        "standing in a castle. The walls are vertical, flat and smooth, " +  
        "and so is the ceiling. It must have been difficult to make this " +
        "place, so there must be a good reason for it.\nYou notice a " +
        "tunnel leading up through the ceiling.\n");

    add_item(({ "tunnel", "space", "open space", }),
        "Part of the wall is carved out to form a large, square " +
        "open space.  Four metal tracks follow the sides up and " +
        "through a dark hole in the ceiling.  You notice the end " +
        "of a rope ladder dangling down from the hole and also " +
        "a crank set into the wall just outside of the tunnel.\n");

    add_item(({ "tracks", "metal tracks" }),
        "The metal tracks are fastened to the cave wall.\n");

    add_item(({ "crank", "pulley", "pulley system", "ropes" }),
        "A crank is attached to the wall here.  A series of pulleys " +
        "and ropes extend up into a tunnel through the ceiling.\n");
    
    add_item(({ "ladder", "rope ladder" }),
        "A small rope ladder dangles down from the ceiling, leading " +
        "up through a tunnel.\n");

    add_exit("lair9", "north", 0, 1);
    add_exit("lair6", "east", 0, 1);
    add_exit("lair1", "south", 0, 1);
    add_exit("", "west", block_west);
    add_exit("cave", "up", block_up, 5, 1);
}

public int
turn_crank(string str)
{
    string arg;
    object platform, oroom;

    if (!strlen(str))
    {
        return 0;
    }

    if ((str != "crank") && !sscanf(str, "crank %s", arg))
    {
        notify_fail("Turn what?\n");
        return 0;
    }

    if ((str == "crank") || ((arg != "clockwise") &&
        arg != "counterclockwise"))
    {
        notify_fail("Do you wish to turn the crank " +
            "clockwise or counterclockwise?\n");
        return 0;
    }

    catch(OTHER_ROOM->load_me());
    if (!(oroom = find_object(OTHER_ROOM)))
    {
        write("The crank won't turn.\n");
        return 1;
    }
   
    if (arg == "clockwise")
    {
        if (!(platform = present("thief_lair_platform", oroom)))
	{
            write("The crank won't turn.\n");
            return 1;
	}

        platform->move(this_object(), 1);
        write("You turn the crank, and a platform jerks down " +
            "from above and comes to rest on the floor.\n");
        say(QCTNAME(this_player()) + " turns a crank, and a platform " +
            "jerks down from above and comes to rest on the floor.\n");
        return 1;
    }
    
    if (!(platform = present("thief_lair_platform")))
    {
        write("The crank won't turn.\n");
        return 1;
    }

    platform->move(oroom, 1);
    write("As you turn the crank, the platform passes up through " +
        "the tunnel, finally stopping at the top.\n");
    say(QCTNAME(this_player()) + " turns a crank, and the platform " +
        "is lifted upwards, disappearing into the dark tunnel " +
        "in the ceiling.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(turn_crank, "turn");

    LOAD_CLONE_HANDLER(THIEF_LAIR_DIR + "clone_handler");
}

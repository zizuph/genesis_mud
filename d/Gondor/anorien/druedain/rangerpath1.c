/*
 *      /d/Gondor/anorien/druedain/rangerpath1.c
 *
 *      Modification log:
 *      25-Jan-1997, Olorin: Revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/forest.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define TRACKING_NEEDED 5

public string  describe();
public string  check_tracking();
public string  exa_track();

public void
create_gondor()
{
    set_short("a forgotten path in the western parts of the Druedain Forest in Anorien");
    set_long(describe);
    set_forest_density(15);

    add_item( ({"path","road"}), "The road is quite overgrown by "
        + "grass, moss and other kinds of undergrowth.\n"
        + "It must be a really long time since it was last used.\n");
    add_item("track", exa_track);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(DRUEDAIN_DIR + "oldroad2", "east",  test_track, 2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad1", "north", test_track, 2, 1);
}

public string
describe()
{
    string  long_descf = "You are on an old path in the western parts "
        + "of the Druedain Forest in Anorien.", 
            time = tod();

    switch (time)
    {
    case "evening":
    case "night":
        long_descf += " It is currently quite dark in the forest, "
            + "since it is " + time + ", and the great trees do not "
            + "let much light through their crowns.";
        break;
    default:
        long_descf += " You see rays of light coming through the "
            + "ceiling of leaves above you, as the sun shines on the "
            + time + " sky.";
    } 
    long_descf += " Tall birches stand all around you, with their "
        + "thick branches tangled together above you as their leaves "
        + "rustle in the breeze. A slightly grass-covered path enters "
        + "from the north and continues east.";
    long_descf += " " + check_tracking();
    return BSN(long_descf);
}

public int
test_time()
{
    string  time  = tod();
    return (time != "evening") && (time != "night");
}

public string
exa_track()
{
    if (TP->query_skill(SS_TRACKING) > TRACKING_NEEDED)
        return "Your skilled eyes discover a track leading south "
            + "through the forest. It is well hidden in the green "
            + "terrain.\n"; 
    else 
        return "You are unable to see any track here.\n";
}

public string
check_tracking()
{
    if (TP->query_skill(SS_TRACKING) > TRACKING_NEEDED)
        return "Your skilled eyes discover a track leading south, though. "+
            "It seems as if someone has skillfully tried to conceal it. ";
    else 
        return "The forest looks too dense to pass through to the south and west.";
}

public int
follow_track(string str)
{
    if (query_verb() == "follow")
    {
        if (!strlen(str) || 
            ((str != "track") && (str != "track south")))
            return 0;
    }

    if (TP->query_skill(SS_TRACKING) < TRACKING_NEEDED) 
    {
        write("You are not able to go that way, the forest is too "
            + "dense, and you cannot find any track to follow.\n");
        return 1;
    }
    write("You skillfully follow the track to the south.\n");
    TP->move_living("south", DRUEDAIN_DIR + "rangerpath2");
    return 1;
}

public void
init() 
{
    ::init();
    add_action(follow_track, "follow");
    add_action(follow_track, "south");
    add_action(follow_track, "s");
}

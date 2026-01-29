/*
 * Coded by Amelia 1/19/98
 * Cobbled road through farm area north of Gont Port
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <macros.h>

public void
create_earthsea_room()
{
    set_short("Wooden bridge");
    set_long("You are standing on an " +
        "arched wooden bridge crossing a small but fast-flowing " +
        "river descending from the mountains. On the east side " +
        "of the bridge the path rises steeply and enters " +
        "the forested area of the mountain. To the west lies " +
        "a green valley with some farm houses along the " +
        "cobblestone road that leads to Gont Port.\n");
    add_item((({"river", "fast-flowing river"})),
        "A small fast-flowing river rushes down from the " +
        "mountains. The wooden bridge crosses it here.\n");
    add_item((({"bridge", "wooden bridge" })),
        "The wooden bridge crosses the small river the Kaheda, " +
        "whose source is somewhere higher on the mountain. " +
        "Looking closer, you see where you can climb down under " +
        "the bridge ... \n");
    add_item((({"buildings", "farm buildings"})),
        "You see some activity among the farm buildings, and " +
        "strangely enough, glints of sun on metal, but it " +
        "is still too hard to make out what is going on.\n");
    add_item((({"mountain", "Gont Mountain"})),
        "The tall mountain climbs steeply to the " +
        "north, covered in dark green forest all the way " +
        "to its snow-covered peak.\n");
    add_item((({"road", "cobbled road"})),
        "The road is made from small stones and crushed " +
        "seashells set together in a kind of cobbled pavement. " +
        "It looks like a ribbon winding over the farmland " +
        "hills to where it disappears at a distance to " +
        "the northeast.\n");
    add_item((({"buildings", "farm buildings"})),
        "The farm buildings are made of stone with thatched roofs. " +
        "To the north you see a barn and a farmhouse, while to " +
        "the south are two other outbuildings.\n");
    add_item((({"farms", "farmland", "herds", "goats", "sheep"})),
        "The farmland scene looks almost perfect with the " +
        "farm houses dotting the hillside and herds of " +
        "white sheep and goats.\n");
    add_exit("cobbled_road6", "west");
    add_exit("south_path_26", "east");
}

public int
climb_down(string str)
{
    object tp = this_player();

    if(str == "down" || str == "down the bridge" ||
        str == "down bridge")
    {
        write("You climb down under the bridge.\n");
        tell_room(this_object(), QCTNAME(tp) +
            " climbs down under the bridge.\n", ({ tp }));
        tp->move_living("M",
            "/d/Earthsea/gont/tenalders/south_path/under_bridge", 1);
        tell_room(environment(tp), QCTNAME(tp) + " climbs in " +
            "from above.\n", ({ tp }));
        return 1;
    }

    return notify_fail("Climb where?\n");
}

public void
init()
{
    ::init();
    write("Your footsteps sound hollow on the wooden bridge, " +
        "and you hear rushing water beneath.\n");
    add_action(climb_down, "climb");
}

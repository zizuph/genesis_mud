/*
 * Coded by Amelia 1/19/98
 * Cobbled road through farm area north of Gont Port
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

public void
create_earthsea_room()
{
    set_short("Green valley");
    set_long("The valley levels a bit between the " +
        "hills. You see farm buildings to the north and south " +
        "set back a short distance from the road. Ahead to the east " +
        "the road crosses a river at a wooden bridge. You hear some " +
        "activity from the farm area. Dirt paths lead north and south from " +
        "here to the buildings.\n");
    add_item((({"bridge", "wooden bridge" })),
        "The wooden bridge crosses the small river the Kahedan, " +
        "whose source is somewhere higher on the mountain.\n");
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
    add_exit("farm_path_1", "north");
    add_exit("farm_path_2", "south");
    add_exit("cobbled_road4", "west");
    add_exit("cobbled_road6", "east");
}

/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

public void
create_earthsea_room()
{
    object door;
    set_short("Village path");
    set_long("The village is situated on " +
        "a somewhat more level area of the mountainside. " +
        "Beyond the village to the north the " +
        "forest continues up to the mountain's peak, which is crowned " +
        "with snow and clouds. Very far away down the mountain " +
        "to the south and east you can see beyond the evergreen forest " +
        "to the vast dark-blue north sea, " +
        "where sunlight sparkles on the waves. " +
        "The high elevation makes for thin air, which is " +
        "scented with pine and herbal smoke coming from chimneys " +
        "of some of the inhabited huts. You see a hut to the west " +
        "with a sign hanging over it, as well as some others to " +
        "the south and southeast.\n");
    add_item("west hut", "Just to the west is a hut with a smoking " +
        "chimney and good smells emanating from it. You see a sign over " +
        "the door.\n");
    add_item("south hut", "There is a hut to the south, where " +
        "you can see people coming and going.\n");
    add_item("southeast hut", "A bit further to the southeast is " +
        "a hut covered in vines.\n");
    add_item((({"sea", "north sea"})),
        "At this elevation you can see all the way to the horizons " +
        "toward the south and east.\n");
    add_item((({"peak", "mountain's peak"})),
        "The snow-covered peak of Gont Mountain is visible through " +
        "a wreath of clouds that surrounds it.\n");
    add_item((({"forest", "evergreen forest"})),
        "The mountain of Gont is flanked with an ancient evergreen " +
        "forest that climbs almost to the peak.\n");
    add_item("mountainside", "The mountainside climbs steeply up " +
        "above the village.\n");
    add_item("village", "This is but a poor peasant village, but " +
        "who knows what mysteries lie beneath its simplicity?\n");
    add_item((({"path", "gravel path"})),
        "A narrow path paved with bits of gravel wanders in between " +
        "the huts.\n");
    add_item((({"huts", "thatch huts"})),
        "With their curved thatched, low roofs, the huts are shaped " +
        "like large mushrooms growing on the mountainside. " +
        "You can examine individual ones that are close to you.\n");
    add_item((({"sign", "wooden sign"})),
        "There are some words on the sign and a figure " +
        "of what appears to be a leaping goat.\n");
    add_exit("village_path_1", "east");
    add_exit("village_path_3", "southwest");
    add_cmd_item(({"sign", "wooden sign"}), "read", "The sign " +
        "reads:\n\n      -+-+The Randy Goat Pub-+-+\n\n");
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/pub_door_out");
    door->move(this_object());
}

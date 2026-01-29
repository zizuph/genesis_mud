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
    set_long("The village rests on a somewhat more level area " +
        "of the mountainside. A gravel path winds among a number of " +
        "low mushroom-shaped thatch huts. Beyond the village to the " +
        "north the forest continues up to the mountain's peak, which " +
        "is crowned with snow and clouds. Very far away down the " +
        "mountain to the south and east you can see beyond the " +
        "evergreen forest to the vast dark-blue north sea, " +
        "where sunlight sparkles on the waves. " +
        "The high elevation makes for thin air, which is " +
        "scented with pine and herb smoke coming from chimneys " +
        "of some of the inhabited huts. There is a " +
        "hut just to the west from here, with a sign " +
        "posted over the door.\n");
    add_item((({"hut", "west hut"})),
        "The hut standing just to the west has a sign " +
        "hanging over the door.\n");
    add_item("sign", "The sign has words on it " +
        "which are legible.\n");
    add_cmd_item("sign", "read", "The sign reads:\n" +
        "      The Peddler Shop.\n");
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
    add_exit("se4", "north");
    add_exit("../south_path/south_path_1", "southeast");
    reset_room();
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/peddler_out");
    door->move(this_object());
}

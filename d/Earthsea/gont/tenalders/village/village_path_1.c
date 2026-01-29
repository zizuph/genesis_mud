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
    set_long("The village rests on a more level area of the " +
        "steep mountainside. A gravel path winds among a number of " +
        "small, mushroom-shaped thatch huts. To the north the " +
        "forest continues up to the mountain's peak, which is crowned " +
        "with snow. Very far away down the mountain " +
        "the view extends all the way to the horizon " +
        "where the sea meets the sky and sunlight sparkles on waves. " +
        "The air is thin due to the high elevation, and it is " +
        "scented with pine and herbal smoke coming from chimneys " +
        "of some of the inhabited huts. Directly to the " +
        "south is a vine-covered hut. To the west " +
        "and east there are others.\n");
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
    add_item((({"small hut", "vine-covered hut", "south hut", "hut",
        "hut to the south" })),
        "There is a small vine-covered hut just to the south, which " +
        "has a small wooden door leading into it.\n");
    add_exit("witch_path", "east");
    add_exit("village_path_2", "west");
    add_exit("se1", "southeast");
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/h_store_out");
    door->move(this_object());
}

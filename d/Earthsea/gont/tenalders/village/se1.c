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
    set_short("Village path");
    set_long("The village rests on a more level area " +
        "of the steep mountainside. A gravel path winds among a number of " +
        "small, mushroom-shaped huts. To the north the forest " +
        "continues up to the mountain's peak, which is crowned " +
        "with snow. Very far away down the mountain " +
        "to the south and east you can see beyond the evergreen forest " +
        "to the vast dark blue north sea, " +
        "where sunlight sparkles on the water. The elevation here is " +
        "quite high, and the thin air is scented " +
        "with pine and herbal smoke coming from chimneys of some of the " +
        "inhabited huts. There is a hut directly to the west of " +
        "you, but there is no entrance from this side.\n");
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
    add_item((({"hut", "west hut"})),
        "The hut to the west is covered with living vines. A distinctive " +
        "herbal fragrance seems to exhude from it. You do not " +
        "see an entrance from this side.\n");
    add_exit("village_path_1", "northwest");
    add_exit("se2", "south");
    reset_room();
}

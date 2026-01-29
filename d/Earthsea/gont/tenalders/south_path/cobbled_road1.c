/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>

public void
create_earthsea_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Cobbled road");
    set_long("The cobblestone road winds steeply up " +
        "toward the northwest, where green farmland blankets the hillside. " +
        "Gont Mountain towers above you, its dark evergreen forest " +
        "extending almost to the snow-covered peak. Here and there " +
        "on the hillside are small farms and flocks of goats and " +
        "sheep. To the southeast you see the " +
        "great dark stone walls of Gont Port just across a " +
        "wooden bridge. Two stone dragons fiercely guard the " +
        "entrance.\n");
    add_item((({"walls", "stone walls"})),
        "The tall walls and towers of Gont Port are " +
        "constructed of dark granite.\n");
    add_item((({"banners", "colourful banners"})),
        "Atop the towers of Gont Port you see " +
        "colourful banners waving in the sea breezes.\n");
    add_item((({"dragons", "stone dragons"})),
        "The dragons look as though they might come alive " +
        "if the city is attacked.\n");
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
    add_item((({"Gont Port", "city"})),
        "The city of Gont Port lies to the south beyond " +
        "a set of dark stone walls surrounded by a moat.\n");
    add_item((({"farms", "farmland", "herds", "goats", "sheep"})),
        "The farmland scene looks almost perfect with the " +
        "farm houses dotting the hillside and herds of " +
        "white sheep and goats.\n");
    reset_room();
    add_exit("/d/Earthsea/gont/gont_city/rooms/out_landbridge", "south");
    add_exit("cobbled_road2", "northwest", 0, 2);
}

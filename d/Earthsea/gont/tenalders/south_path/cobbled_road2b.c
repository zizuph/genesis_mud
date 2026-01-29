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
    set_short("Cobbled road");
    set_long("The cobblestone road lies like a " +
        "ribbon across green farmland on the rolling hillside. " +
        "Gont Mountain towers above with its dark green forest " +
        "extending almost to the snow-covered peak. Here and there " +
        "on the hillside are small farms and flocks of goats and " +
        "sheep, making this pastoral scene almost perfect. The " +
        "road makes a sharp bend here around a large oak tree, " +
        "going down toward the southwest and rising steeply to the " +
        "northwest. Some distance to the south you make out the " +
        "dark granite walls of Gont Port.\n");
    add_item((({"tree", "oak tree", "large oak tree"})),
        "The old oak tree is a grandfather of trees, and apparently " +
        "rather than cut it down, the road was built around it.\n");
    add_item((({"walls", "stone walls"})),
        "The tall walls and towers of Gont Port are " +
        "constructed of dark granite.\n");
    add_item((({"banners", "colourful banners"})),
        "Atop the towers of Gont Port you see " +
        "colourful banners waving in the sea breezes.\n");
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
    add_exit("cobbled_road2c", "northwest", 0, 3);
    add_exit("cobbled_road2a", "southwest");
    add_cmd_item((({"tree", "oak tree"})), "climb",
        "The large oak tree towers above you, but you find no " +
        "foothold to climb up.\n");
}

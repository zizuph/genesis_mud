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
        "sheep, making this pastoral scene almost perfect. From " +
        "here looking back to the southwest, you can see the " +
        "dark stone walls of Gont Port with its high towers. " +
        "Between the Armed Cliffs you see the busy harbour " +
        "with its many colourful ships. To the east the road " +
        "dips down into a valley.\n");
    add_item((({"Armed Cliffs", "harbour", "busy harbour"})),
        "From here you can see the famous Armed Cliffs that " +
        "protect the busy harbour of Gont Port with their " +
        "natural fortifications.\n");
    add_item((({"ships", "colourful ships"})),
        "This appears to be a very busy harbour " +
        "with many ships with colourful sails.\n");
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
    add_exit("cobbled_road3", "west");
    add_exit("cobbled_road4", "east");
}

public void
init()
{
    ::init();
    write("You climb to the hilltop and pause for a moment " +
        "to survey the surrounding countryside.\n");
}

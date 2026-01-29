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
    set_long("The cobblestone road leads east " +
        "to a wooden bridge crossing a small river. " +
        "The road becomes an unpaved path on the other side of " +
        "the bridge, which climbs into the forested hills. " +
        "To the west the cobblestone road runs past a farm then " +
        "uphill out of the valley.\n");
    add_item((({"bridge", "wooden bridge" })),
        "The wooden bridge crosses the small river the Kahedan, " +
        "whose source is somewhere higher on the mountain.\n");
    add_item((({"buildings", "farm buildings"})),
        "You see some activity among the farm buildings, and " +
        "strangely enough, glints of sun on metal, but it " +
        "is still too hard to make out what is going on.\n");
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
    add_exit("cobbled_road5", "west");
    add_exit("bridge", "east");
}

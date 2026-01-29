/*
 * Coded by Amelia 11/22/97
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define GIRL "/d/Earthsea/gont/gont_city/liv/girl"

private object girl;

public void
reset_room()
{
    if(!objectp(girl))
    {
        girl = clone_object(GIRL);
        girl->move(this_object(), 1);
        girl->command("emote comes skipping in.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Attic room");
    set_long("The ceiling of this attic room "+
        "is bare wooden planks, and you can see the arch of the roof. "+
        "This looks like a loft where someone sleeps. There is a "+
        "small bed against one wall, which has a patchwork quilt "+
        "spread neatly upon it. There is a wooden box on the floor "+
        "and a carved wooden horse, which is just big enough for a "+
        "child to play on.\n");
    add_item((({"bed", "small bed", "patchwork quilt", "quilt"})),
        "Apparently this is a child's bed. It is covered with a "+
        "colourful patchwork quilt and looks very comfortable.\n");
    add_item((({"box", "wooden box"})),
        "You look in the wooden box on the floor by the "+
        "foot of the bed and see some small toys in it, among them "+
        "blocks and a ball.\n");
    add_item((({"ceiling", "attic room"})),
        "The bare rafters of this attic are exposed and make the "+
        "ceiling rather low.\n");
    add_item((({"horse", "wooden horse", "carved wooden horse"})),
        "The wooden horse is just large enough for a child to "+
        "ride. It has rockers under the feet.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("house", "down");
    reset_room();
}

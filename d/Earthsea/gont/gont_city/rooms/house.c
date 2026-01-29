/*
 * Coded by Amelia 11/22/97
 */

#pragma no_clone
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#define DOOR "/d/Earthsea/gont/gont_city/obj/house_in"
#define MOTHER "/d/Earthsea/gont/gont_city/liv/mother"

private object mother;

public void
reset_room()
{
    if(!objectp(mother))
    {
        mother = clone_object(MOTHER);
        mother->move(this_object(), 1);
        mother->emote("enters.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Small house");
    set_long("Inside the house. "+
        "This is a small but comfortable room. You see an "+
        "oak table with a vase of flowers on it. Light filters in "+
        "through colourful curtains which cover the window looking "+
        "out over the yard. Hanging on a hob in the open hearth, an iron "+
        "kettle bubbles merrily with the day's soup, which "+
        "smells delicious. You see a stone basin filled with "+
        "fresh water on a counter under the window. There is a "+
        "stairway that leads up "+
        "to the next floor, and a doorway leads to another room "+
        "just north.\n");
    add_item("stairway", "A narrow wooden stairway leads up "+
        "to the next floor.\n");
    add_item((({"vase", "flowers", "table", "oak table"})),
        "A sturdy oak table sits in the center of the room, and "+
        "a vase filled with red flowers decorates it.\n");
    add_item((({"curtains", "window", "flower-print curtains" })),
        "Some colourful curtains cover the window and permit "+
        "some privacy, however, they are thin enough to let in "+
        "lots of light.\n");
    add_item((({"kettle", "iron kettle", "hob", "hearth",
        "open hearth"})),
        "There is a large hearth set in the east wall with a "+
        "low fire burning under an iron kettle. The kettle appears to "+
        "be bubbling away, and you smell the aroma of bouillabase, "+
        "a type of seafood soup.\n");
    add_item((({"basin", "stone basin", "counter"})),
        "A wooden counter stands under the window. It has a stone "+
        "basin filled with fresh water upon it.\n");
    add_prop(ROOM_I_INSIDE, 1);
    clone_object(DOOR)->move(this_object(), 1);
    add_exit("house_upstairs", "up");
    add_exit("house2", "north");
    reset_room();
}

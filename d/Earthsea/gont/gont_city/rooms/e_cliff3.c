#pragma strict_types
#pragma no_clone

inherit "/std/room";
#include <stdproperties.h>

#define SANDAL "/d/Earthsea/gont/gont_city/obj/sandal"
#define BEACH_CLIFF "/d/Earthsea/gont/beach/cliff_rooms/cliff01"

private object sandal;

public void
reset_room()
{
    object to = this_object();

    if(!present("sandal", to))
    {
        sandal = clone_object(SANDAL);
        sandal->move(to);
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("East cliff of the Armed Cliffs");
    set_long("This is the east wing of the "+
    "Armed Cliffs which embrace the harbour of Gont Port like a "+
        "fist. You are on a narrow gravel path which runs north and "+
        "south from here along the cliff's edge. "+
        "There is a magnificent view of the surrounding area "+
        "and coast; however, you feel a touch of vertigo from "+
        "the steep heights. A stairway carved from granite "+
        "leads downward towards the beach.\n");
    add_item((({"view", "magnificent view", "surrounding area",
        "sea", "cliff", "coast", "city", "Gont Port"})),
        "The Armed Cliffs of Gont Port protect the harbour "+
        "from attack. From here you see a magnificent view of the "+
        "the dark blue sea and the coast that extends west and "+
        "east from here. The cliff overlooks a white sandy beach "+
        "to the east, where you see waves lapping against the "+
        "shore. To the north you see the activity of Gont Port "+
        "stretching out below with many sailors, guards and "+
        "citizens on their daily business. There are many boats "+
        "at harbour here, but way to the east you see three "+
        "black longships with the sign of Karego At upon their "+
        "sails. Far to the north Gont Mountain stands majestic "+
        "above the city, with its forested flank reaching up to "+
        "a snowcapped peak swathed in clouds.\n");
    add_item((({"tower", "granite tower", "guard tower"})),
        "The granite guard tower standing just to the east looks "+
        "out over the coast.\n");
    add_item((({"stairway","step", "top step", "granite stairway"})),
        "You see a granite stairway carved into the stone that "+
        "leads downward towards the beach.\n");
    add_exit(BEACH_CLIFF, "down");
    add_exit("e_cliff4", "north");
    add_exit("e_cliff2", "south");
    reset_room();
}

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("East cliff of the Armed Cliffs");
    set_long("This is the east side of the "+
        "Armed Cliffs which embrace the harbour of Gont Port like a "+
        "fist. You are at the top of the cliffs, and there is a "+
        "magnificent view of the surrounding area. "+
        "There is a guard tower just to the southeast from here, "+
        "which looks out over the coast. There is a narrow path that "+
        "leads north and south.\n");
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
    add_exit("e_cliff3", "north");
    add_exit("e_cliff1", "south");
}

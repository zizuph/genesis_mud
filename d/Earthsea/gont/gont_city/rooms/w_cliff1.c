#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
inherit "/std/room";

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("West cliff of the Armed Cliffs");
    set_long("This is the west side of the "+
        "Armed Cliffs which embrace the harbour of Gont Port like a "+
        "fist. You are at the top of the cliffs, and there is a "+
        "magnificent view of the surrounding area. Apparently that "+
        "is why there is a guard tower here, so that the city may "+
        "be defended against besieging Kargs, pirates, and smugglers. "+ 
        "The tower is just to the west and looks out over the "+
        "sea coast to the south and west and over the city to the "+
        "north and east. There is a stairway that leads down "+
        "toward the city.\n");
    add_item((({"view", "magnificent view", "surrounding area",
        "sea", "cliff", "coast", "city", "Gont Port"})),
        "The Armed Cliffs of Gont Port protect the harbour "+
        "from attack. From here you see a magnificent view of the "+
        "dark blue sea and the coast that extends west and "+
        "east from here. The Cliffs overlook a white sandy beach "+
        "some distance to the "+
        "to the east, where you see waves lapping against the "+
        "shore. To the northeast you see the activity of Gont Port "+
        "stretching out below with many sailors, guards and "+
        "citizens on their daily business. There are many boats "+
        "at harbour here, but way to the east you see three "+
        "black longships with the sign of Karego At upon their "+
        "sails. Far to the north Gont Mountain stands majestic "+
        "above the city, with its forested flank reaching up to "+
        "a snowcapped peak swathed in clouds. Above the city you "+
        "see another cliff jutting out from the mountainside, the "+
        "Overfell, and the village of Re Albi, the Falcon's "+
        "Nest. Some distance to the west the island of Oranea "+
        "is a dreamlike line between sea and sky, floating in the "+
        "blue mist.\n");
    add_item((({"tower", "granite tower", "guard tower"})),
        "The granite guard tower standing just to the west looks "+
        "out over the coast.\n");
    add_exit("west_stairs", "down");
    add_exit("gran_tower2", "west");
}

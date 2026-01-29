#pragma strict_types
#pragma no_clone

inherit "/std/room";
#include <stdproperties.h>


#define ROC_SIGN "/d/Earthsea/gont/gont_city/obj/roc_sign"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("East cliff of the Armed Cliffs");
    set_long("You are standing on a heap "+
        "of granite boulders overlooking the east side of the "+
        "Armed Cliffs of Gont Port. Among the boulders are smaller "+
        "black rocks which remind you of the droppings of a very "+
        "large bird. You get a touch of vertigo while looking down "+
        "from these heights over the cliffs to see the sea so far "+
        "below, crashing on a sandy white beach to the east. To "+
        "the north Gont Mountain towers above, its snowy peak "+
        "wreathed with clouds.\n");
    add_item((({"view", "magnificent view", "surrounding area",
        "Gont Mountain", "gont mountain", "Armed Cliffs",
        "armed cliffs", "sea", "beach", "sandy white beach",
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
    add_item((({"rocks", "black rocks", "boulders",
        "granite boulders"})),
        "The large granite boulders are arranged in the shape "+
        "of a giant eyrie or nest. Smaller black rocks appear to "+
        "be the droppings from some very large bird...\n");
    add_exit("e_cliff4", "down");
    clone_object(ROC_SIGN)->move(this_object(), 1);
}

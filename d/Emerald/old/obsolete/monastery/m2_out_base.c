#include "defs.h"

inherit MONASTERY_BASE;

void
create_m2_room()
{
}

nomask void
create_monastery_room()
{
    set_short("On the second-storey walkway");

    set_em_long("This wide, stone walkway runs around the outside of " +
        "the courtyard on the second storey, following the monastery " +
        "walls around to a pair of entrances to the main building to " +
        "the east.\n");

    add_item(({ "entrance", "entrances", "entrances to main building",
        "archway", "archways" }),
        "Two archways, one at the northern end and another at the " +
        "southern end of the walkway lead into the main monastery " +
        "building to the east.\n");

    add_item("garden", 
        "The sad remains of what was obviously once a well-tended " +
        "garden encompass the majority of the courtyard.  Trampled " +
        "and neglected, most of the flowers, bushes, and herbs planted " +
        "here have died, giving way to weeds.\n");
    
    add_item(({ "plants", "flowers", "bushes", "herbs", "weeds" }),
        "Trampled and neglected, most of the flowers, bushes, and herbs " +
        "planted here have died, giving way to weeds.\n");

    add_item("courtyard",
        "A large courtyard just inside the monastery walls, it was " +
        "probably a place of great beauty at one time, but now it " +
        "shows the signs of neglect.  What was once a large garden in " +
        "the center of the courtyard is now overgrown with weeds.\n");

    add_item(({ "walls", "monastery walls", "perimeter", "upper levels" }),
        "High, stone walls surround the courtyard, forming a three-storey " +
        "perimeter.  To the east is the main building of the monastery " +
        "itself, while to the north, south, and west, a wide walkway " +
        "surrounds the courtyard on the ground level, with another " +
        "elevated walkway on the storey above it; an enclosed hallway " +
        "forms the top storey.\n");

    add_item(({ "ground level", "first storey", "first storey walkway",
        "first-storey walkway", "wide walkway", "walkway" }),
        "A wide, stone walkway surrounds the courtyard on the ground " +
        "level, bounded by the monastery walls on the outside and the " +
        "garden on the inside.  A series of heavy pillars support the " +
        "second-storey walkway.\n");

    add_item(({ "second storey", "second storey walkway", 
        "second-storey walkway", "elevated walkway" }),
        "An elevated walkway that runs along the inside of the " +
        "monastery walls and leads into the second storey of the main " +
        "monastery building to the east.  A series of heavy pillars " +
        "support the third storey.\n");

    add_item(({ "third storey", "hallway", "enclosed hallway" }),
        "The third storey is enclosed, forming a hallway that apparently " +
        "leads into the third storey of the main building of the monastery " +
        "to the east.\n");

    add_item(({ "building", "main building", "monastery", "east" }),
        "The stone structure of the three-storey main building of the " +
        "monastery stands to the east of the courtyard.  From the " +
        "outside, it appears that it has been damaged inside, judging " +
        "by the cracked and broken windows.\n");

    add_item(({ "windows", "cracked windows", "broken windows" }),
        "The windows look very dirty, and many have been cracked or " +
        "broken out completely.\n");
       
    add_item(({ "pillars", "heavy pillars" }),
        "Heavy, stone pillars support the upper levels of the monastery.\n");

    create_m2_room();
}

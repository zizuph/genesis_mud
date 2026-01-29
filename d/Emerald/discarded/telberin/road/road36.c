/*
 * Lakeside road that goes to the crossroad of Telberin
 * Based on the kroad files
 * By Finwe
 * January 1997
 */
 
#include "../default.h"
 
inherit LAKEROAD;
 
int no_way();

void
create_road()
{
    set_short("A twisty mountain road");
    set_long("   The road twists and turns as it winds its way " +
        "up into Mt. Black, leaving the lake and forest behind. " +
        "Jagged peaks can be seen in the distance against the " +
        "mountain. The top of the mountain constantly spews smoke, " +
        "giving it a dark and forbidding look. A rocky road " +
        "continues into the mountain.\n\n");
    add_item(({"rocks", "rocky road", "road"}),
        "barren and gray. The vegetation is sparse because it has " +
        "to cling to life here in the mountains.\n");
    add_item("vegetation",
        "The vegetation consists of dwarfed trees, and " +
        "scrub brush.\n");
    add_item("trees",
        "Closer to the lake and out of the mountains, the trees " +
        "are healthy and vibrant. Here in the mountains, they " +
        "are scraggly and dwarfed.\n");
    add_item(({"dwarf trees", "dwarfed trees"}),
        "The trees have been treated poorly by the elements. " +
        "They are mishaped and look rugged. The trees grow in " +
        "what seems to be rock, but manage to survive in the " +
        "poor conditions. This is rather amazing considering the " +
        "volcanic activity here.\n");
    add_exit("/d/Emerald/mountains/mtblack/road01", "northwest");
    add_exit("", "east", no_way);
   add_exit(LROAD + "road35", "southeast");
}
 
int
no_way()
{
    write("You notice that you can no longer go this way. A " +
        "landslide blocks the road, preventing anyone from " +
        "going further into the mountains.\n");
    return 1;
 
}

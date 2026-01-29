// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In the castle courtyard");
    set_long("You stand in a grassy courtyard right before "+
        "the large castle that dominates the Noble district. "+
        "The castle walls rise directly to your south. The ground "+
        "below is hard and there are many nicely trimmed bushes " +
        "sprouting about. A statue stands off to your west.\n");
    add_item(({"walls","castle"}),"The castle walls are made of grey stone "+
        "brick and mortar. As you gaze up, you see that they don't "+
        "reach very high up, but the towers do. You see many little "+
        "windows facing out of the walls.\n");
    add_item("bushes","Neat trimmed bushes.\n");
    add_item("statue","A statue of an ancient warrior stands off "+
        "to the west.\n");
    
    add_exit(NOBLE + "wayfarer/s9", "north", 0, 0);
    add_exit(NOBLE + "castle/g3", "west", 0, 0);
    add_exit(NOBLE + "castle/g5", "southeast", 0, 0);
}


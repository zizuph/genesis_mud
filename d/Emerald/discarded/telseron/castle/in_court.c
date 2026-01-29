/*
 * The inner court of the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"

void reset_room();
 
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("The inner court");
    set_long("   You stand in the inner court, just past the " +
        "portico. The courtyard is large and bright. The walls " +
        "are expertly covered with mother of pearl. The room " +
        "shines as light pours in from windows, filling the court " +
        "and dazzling your senses. The room almost seems to glow. " +
        "The court is quite busy as elves come and go. A great " +
        "arch opens south into the castle while another arch leads " +
        "out to the portico.\n\n");
 
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface so perfectly " +
        "covered that you don't detect any seams. The walls have been "+
        "polished and are smooth to the touch.\n");
    add_item(({"floor", "ground", "down"}),
        "Like the walls, the floor is faced with mother of pearl. " +
        "It is polished to an incredible sheen from the number " +
        "feet that walk across it. Yet, the floor doesn't show " +
        "show any sign of wear and tear.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling is amazing. Inlaid into the mother of pearl " +
        "is emerald, shaped as twining leaves, stems, and flowers. " +
        "The effect catches your breath as the ceiling twinkles " +
        "in the sun.\n");
    add_item("arch",
        "The arches are large and circular. One leads south into the " +
        "castle while the other goes north into the city.\n");
    add_item(({"window", "windows"}),
        "The windows are expansive and fill the room with light. " +
        "They are arched shaped.\n");
 
    add_exit( TCASTLE_DIR + "portico", "north");
    add_exit( TCASTLE_DIR + "cor02",     "south");
}

void
reset_room()
{
}

/*
 * The music room in the castle in Telseron
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
    set_short("The royal music room");
    set_long("   The music room is large and well used. Your " +
        "movements echo as you move around the room. The acoustics " +
        "of the room are incredible as sound seems to resonate " +
        "controllably within here. As you move around, you notice " +
        "certain parts of the room act like private practice " +
        "chambers, permitting musicians to practice their art " +
        "without disturbing others. Many elves come here to practice " +
        "their music and create new songs. Many instruments line the " +
        "walls here. Some are recognizable but others are some you " +
        "haven't seen before. All the instruments are in perfect " +
        "condition. North and west of you leads to corridors while " +
        "east takes you to the Great Hall.\n\n");


    add_item("chambers",
        "The chambers are soundproof pockets in the room. Elves " +
        "find them by the geometric patterns on the floor.\n");
    add_item(({"mark", "marks", "geometric marks", "geometric mark"}),
        "The geometric marks are inlaid into the floor. They are " +
        "made of mahogany and discreetly blend into the floor.\n");

    add_item(({"up", "ceiling"}),
        "The ceiling is richly decorated with paintings of elven " +
        "musicians. Some are singing, others are playing instruments " +
        "and others are perfoming for the King and Queen.\n");
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface is so perfectly " +
        "covered you don't detect any seams. The walls have been "+
        "polished and are smooth to the touch.\n");
    add_item(({"floor", "ground", "down"}),
        "The floor is constructed of polished hardwood. A pattern " +
        "of interlocking shapes makes up the design of the floor.\n");
    add_item("instruments",
        "You see wind, string, percussion, keyboards, and " +
        "other instruments. They are stored in glass cases " +
        "lining the walls.\n");
    add_item(({"wind", "wind instruments"}),
        "You see flutes, panpipes, fifes, shawms, crummhorns, " +
        "bassons, oboes, and many other wind instruments.\n");
    add_item(({"strings", "string instruments"}),
        "You see lutes, mandolins, lyres, violins, violas, " +
        "harps, dulcimers, and many other string instruments.\n");
    add_item(({"percussion", "percussion instruments"}),
        "Displayed are rainsticks, drums, triangles, xylophones, " +
        "tamborines, rattles, and other percussion instruments.\n");
    add_item(({"keyboard", "keyboards", "keyboard instruments"}),
        "Looking around, you see a few grand pianos, some " +
        "harpsichords, an organ, and other keyboard instruments.\n");

    add_exit( TCASTLE_DIR + "cor01",  "north");
    add_exit( TCASTLE_DIR + "g_hall", "east");
    add_exit( TCASTLE_DIR + "cor04",  "west");
}

void
reset_room()
{
}

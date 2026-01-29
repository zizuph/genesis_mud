/*
 * The portico of the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"

void reset_room();

 
void
create_room()
{
    reset_room();
    set_short("The castle portico");
    set_long("   You stand in the portico of the castle. This " +
        "large porch is open and impressive. Grand pillars surround " +
        "the parameter of the portico, supporting the massive " + 
        "roof. Built of stone, it is expertly faced with " +
        "mother of pearl. The portico shines as light fills it, " +
        "dazzling your senses. The area seems to glow. The porch " +
        "is quite busy as elves come and go. Stairs lead down to " +
        "the outer court.\n\n");
 
    add_item(({"floor", "ground", "down"}),
        "Like the walls, the floor is faced with mother of pearl. " +
        "It is polished to an incredible sheen from the number " +
        "feet that walk across it. Yet, the floor doesn't show " +
        "show any sign of wear and tear.\n");
    add_item("arch",
        "The arch is large and circular. It leads south into the " +
        "castle.\n");
    add_item(({"pillars", "pillar", "column", "columns"}),
        "The pillars are large. They have been carved into the " +
        "shape of large trees, whose branches support the pediment.\n");
    add_item("pediment",
        "This low trianglular shaped stone sits on top of the outer " +
        "pillars and defines the entrance to the castle. In its center " +
        "are relief statues of elven warriors defending the city.\n");
    add_item(({"stair", "stairs", "staircase"}),
        "Great stone stairs, faced with mother of pearl descend to the " +
        "outer court of the castle.\n");
 
    add_exit( TCASTLE_DIR + "in_court", "south");
    add_exit( TCASTLE_DIR + "out_court", "down", "@@downstairs@@");
} 
 

int downstairs()
{
    write ("You descend the stairs to the outer court.\n");
 
    say(QCTNAME(TP) + " descends the stairs to the outer court.\n");
}

void
reset_room()
{
}

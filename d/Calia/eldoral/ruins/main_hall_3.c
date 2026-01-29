#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in a wide hallway in the ruins of " + CASTLE_NAME);
    set_long("You are in a wide hallway, through the heart " +
        "of the ruins of "+CASTLE_NAME+". Unlike the other corridors " +
        "you've seen, this one has a massive, vaulted ceiling, " +
        "with braces curving upwards along the walls to join " +
        "at the apex of the arched ceiling. Light streams " +
        "into the hall from several narrow openings that " +
        "line the ceiling at regular intervals all down the " +
        "length of the hallway, the shafts of light " +
        "illuminating the dusty surfaces, causing swirling " +
        "dust to look like dancing ghosts in the darkness. " +
        "All of the surfaces are made from carefully crafted " +
        "and assembled blocks of the same grey stone that " +
        "dominates these ruins. A narrow archway branches "+
        "off towards the north, and to the east the " +
        "hallway opens up into a huge room.\n\n");

    add_item(({"ceiling", "roof"}),
        "Above your head, the fine stonework which went into " +
        "the construction of the vaulted ceiling appears to " +
        "have paid off, as the arched columns have almost " +
        "completely prevented any real damage. Besides a " +
        "few cracks, it seems to be completely intact.\n");
    add_item(({"braces", "columns"}),
        "Tall, gracefully curving columns rise from the floor, " +
        "arching inwards to meet each other in pairs down the " +
        "length of the corridor.\n");
    add_item(({"walls"}),
        "The walls are strongly constructed from large blocks of " +
        "grey stone, which seems to have stood up rather well " +
        "to the passage of time. In fact, short of some crumbling " +
        "evident near the windows higher up, they look much like " +
        "they must have looked untold years ago.\n");
    add_item(({"windows", "window"}),
        "High in the walls, long windows rise vertically, allowing " +
        "ribbons of light to slice downwards through the dust.\n");
    add_item(({"floor", "ground"}),
        "The floor is made from carefully-placed flagstones, and " +
        "is in good shape, aside from a few places where water " +
        "has discoloured them over the years.\n");

    INSIDE;

    add_exit(RUIN + "ne_alley", "north");
    add_exit(RUIN + "main_hall_4", "east");
    add_exit(RUIN + "main_hall_2", "west");
}

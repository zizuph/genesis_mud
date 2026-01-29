#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("upon a wide staircase");
    set_long("You are upon a wide staircase that seems " +
        "to pass down a passage carved out of solid " +
        "stone. The smoothly finished walls arc " +
        "together, giving the stairway a dome-shaped " +
        "ceiling. At numerous points along the walls, "+
        "iron sconces hang in rust-covered silence. " +
        "The stairs descend into darkness, but you " +
        "think it looks to be brighter above.\n\n");

    add_item(({"walls", "ceiling", "roof"}),
        "The walls seem to be cut from solid stone, and " +
        "polished smooth. They curve gracefully towards each " +
        "other, meeting each other above your head to form " +
        "the ceiling.\n");
    add_item(({"sconces"}),
        "Once the rusted iron rings would have held torches, " +
        "lighting up this stairway, but not they hold nothing " +
        "but rust and dust.\n");
    add_item(({"stairs"}),
        "The stairs themselves also appear to be carved from " +
        "the surrounding stone. Aside from some chipping and " +
        "crumbling at the edges of each step, they also appear " +
        "to be in fine condition.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "main_hall_4", "up");
    add_exit(RUIN + "e_tunnel_5", "down");
}


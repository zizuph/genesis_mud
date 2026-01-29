/*
 * File:    garden
 * Creator: Cirion, 1998.06.14
 * Purpose: Garden in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("garden");
    set_long("Tiny red flowers carpet the soft ground of this "
        + "peaceful circular garden. Rising in the center of the place is a tall "
        + "linden tree in full bloom, creating an area of cool shade "
        + "around it. A small gravel path circles the tree. To the "
        + "north, a wide archway opens into the great hall, "
        + "and enclosing the garden are four small stone buildings, which "
        + "open to the northwest, northeast, southwest, and southeast. "
        + "The whole garden breathes with life and joy.\n");
    add_item(({"branch","branches","pile"}),
        "There is a small pile of branches stacked near the "
        + "entrance to the monestary, drying in the sun.\n");
    add_item(({"sun","sunlight"}),
        "The sunlight filters through the leaves of the "
        + "linden tree, forming mottled fragmented patterns "
        + "that dance around magically.\n");
    add_item(({"ground","path","gravel"}),
        "The gravel path circles around the linden tree in "
        + "the center of the garden, branching out to the "
        + "four buildings at the corners.\n");
    add_item(({"wall","walls"}),
        "The garden walls around are made from neatly-fit "
        + "blocks of grey stone.\n");
    add_item(({"building","buildings"}),
        "There are four stone buildings at the corners of "
        + "the garden with open doorways.\n");
    add_item(({"tree","linden","branches"}),
        "The soft light wood of the linden tree blossoms at "
        + "the end with cymes of light yellow flowers, and "
        + "large cordate leaves. It offers shade and "
        + "coolness to the garden, the movements of its "
        + "leaves causing the sunlight to dance gently upon "
        + "the gravel path.\n");
    add_item(({"leaf","leaves","cordate"}),
        "They are heart-shaped, and sway in the breeze.\n");
    add_item(({"flower","flowers","red flowers"}),
        "They are tiny red flowers, called by some Dragon "
        + "Blood.\n");
    add_item("archway",
        "It is a wide arch that opens north into the great "
        + "hall.\n");


    WIZINFO("This is the garden in the monks guildhall.\n");

    // where, command
    add_exit("hall_lower_south", "north");
    add_exit("training_ua", "northwest");
    add_exit("training_defence", "northeast");
    add_exit("training_focus", "southwest");
    add_exit("training_other", "southeast");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("north", "You walk down the short passage and emerge "
        + "in the brightly-lit garden.\n");
}


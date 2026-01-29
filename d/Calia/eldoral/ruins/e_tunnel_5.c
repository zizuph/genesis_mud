#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in a large chamber beneath " + CASTLE_NAME);
    set_long("You have entered a large room which has " +
        "been carved from solid stone, it appears. The " +
        "ceiling itself is fairly low, but the walls are " +
        "quite far apart, giving the chamber a spacious " +
        "feel to it. The chamber empties directly into " +
        "a tunnel to the north, and in the center of " +
        "the wall to the south, a wide stone staircase " +
        "descends down into the center of the room. The " +
        "walls are in remarkably good condition, " +
        "compared to the other ruins you've seen, " +
        "though the wide granite steps of the staircase " +
        "have had their front edge chipped and worn " +
        "quite heavily. Standing on either side of the " +
        "stone staircase, two statues stand at sharp " +
        "attention for all eternity. Judging by their " +
        "condition, however, they won't last that long. " +
        "The stone has already begun to crack in a few " +
        "places, given a few hundred more years parts " +
        "may start falling off.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling above your head is low, but arched slightly " +
        "in the center to give it more height, and cut from solid " +
        "stone.\n");
    add_item(({"walls"}),
        "The walls of the room flare outward from the exit to " +
        "north towards the back wall to the south, giving it a " +
        "semi-spherical shape.\n");
    add_item(({"floor", "ground"}),
        "The floor has been carefully cut and smoothed from the " +
        "surrounding stone.\n");
    add_item(({"stairway", "staircase", "stairs"}),
        "A wide stone staircase ascends upwards against the " +
        "south wall, and projects out into the center of the " +
        "room. Smooth bannisters of stone flank the wide " +
        "granite steps.\n");
    add_item(({"statues"}),
        "The statues are of a man and a woman, though you " +
        "recognize neither of them. Each bears its head in " +
        "an almost noble fashion; perhaps they " +
        "were royalty.\n");


    INSIDE;
    DARK;

    add_exit(RUIN + "e_tunnel_4", "north");
    add_exit(RUIN + "main_stairs_n", "up");
}

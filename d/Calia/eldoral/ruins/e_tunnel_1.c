#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in a narrow corridor");
    set_long("You are in a narrow corridor in the eastern " +
        "parts of the ruins. The construction here is a bit " +
        "strange, the western wall looks to have been cut from " +
        "solid stone, where the eastern wall has been constructed " +
        "from large stone blocks. Aside from that it's quite " +
        "ordinary, with the floor also cut from stone, and the " +
        "ceiling built from a series of large stone slabs laid " +
        "horizontally between the walls. " +
        "To the north the tunnel emerges " +
        "onto a wide courtyard of some sort, and a separate, " +
        "wider tunnel branches westwards from here.\n\n");

    add_item(({"ceiling", "roof"}),
        "Above your head, long slabs of stone rest across the " +
        "tops of the walls, forming the low ceiling.\n");
    add_item(({"floor", "ground"}),
        "The ground seems to be bare stone, cut from the " +
        "surrounding stone and smoothed for a walking surface.\n");
    add_item(({"walls"}),
        "The eastern wall is comprised of large stone blocks, many " +
        "of which sport large cracks and missing chunks where the " +
        "stone has crumbled. The west wall appears to be cut from " +
        "solid stone, however, and is still in good condition. " +
        "Rusted iron sconces serve as the only decoration on " +
        "either wall.\n");
    add_item(({"sconces"}),
        "The sconces are simple iron rings embedded in the walls. " +
        "Once they'd have held torches, now all the hold is rust.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "ne_court_se", "north");
    add_exit(RUIN + "e_tunnel_4", "west");
    add_exit(RUIN + "e_tunnel_2", "south");
}

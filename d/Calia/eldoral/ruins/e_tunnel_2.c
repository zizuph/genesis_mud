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
        "normal, with the floor also cut from stone, and the " +
        "ceiling built from a series of large stone slabs laid " +
        "horizontally between the walls. The walls themselves " +
        "carry rusted out iron sconces, and the eastern " +
        "wall is badly pitted where chunks of " +
        "stone have crumbled or cracked off with the passing " +
        "of the years.\n\n");

    add_item(({"ceiling", "roof"}),
        "Above your head, long slabs of stone rest across the " +
        "tops of the walls, forming the low ceiling.\n");
    add_item(({"floor", "ground"}),
        "The ground seems to be bare stone, cut from the " +
        "surrounding stone and smoothed for a walking surface.\n");
    add_item(({"walls", "wall"}),
        "The eastern wall is comprised of large stone blocks, many " +
        "of which sport large cracks and missing chunks where the " +
        "stone has crumbled. The west wall appears to be cut from " +
        "solid stone, however, and is still in good condition. " +
        "Rusted iron sconces serve as the only decoration on " +
        "either wall.\n");
    add_item(({"sconces", "sconce", "iron sconce", "iron sconces"}),
        "The sconces are simple iron rings embedded in the walls. " +
        "Once they'd have held torches, now all the hold is rust.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "e_tunnel_1", "north");
    add_exit(RUIN + "e_tunnel_3", "south");
}

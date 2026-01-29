#pragma strict_types

#include "defs.h"

inherit STDROOM;
inherit CRYPTDOORS;

public void
reset_room()
{
    ::reset_room();
    reset_doors();
}

public void
create_room()
{
    set_short("in a narrow corridor");
    set_long("You are in a narrow corridor, probably in the " +
        "eastern parts of the ruins, you decide. The construction " +
        "here is a bit odd, as the western side of the passage " +
        "seems to be carved from solid stone, while the eastern " +
        "wall looks to have been constructed from blocks of " +
        "stone. While it looks quite solid, apparently it wasn't " +
        "solid enough, as further passage to the south through " +
        "the corridor is completely blocked by a massive pile " +
        "of rubble where it looks like part of the eastern wall " +
        "caved in. The passage is quite clear towards the north, " +
        "however, and a huge pair of stone doors stand against " +
        "the west wall, and appear to be undamaged.\n\n");

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
    add_prop(ROOM_I_NO_CLEANUP, 1);
    DARK;

    add_exit(RUIN + "e_tunnel_2", "north");
    add_crypt_door(RUIN + "crypt_8", "west");

    set_alarm(0.0, 0.0, reset_room);
}

public void
init()
{
    ::init();
    init_doors();
}


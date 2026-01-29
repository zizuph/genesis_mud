#include "defs.h"

inherit "/std/room";

public int
grotto_msg()
{
    write("You head eastwards for a short distance, and emerge " +
        "in a dark grotto.\n");
    return 0;
}

public int
west_block()
{
    if (TP->query_real_name() != "firestorm")
    {
        write("You somehow can't bring yourself to proceed " +
            "in that direction.\n");
        return 1;
    }
    else
        return 0;
}

public void
create_room()
{
    set_short("a water-filled tunnel");
    set_long("You are in a wide tunnel that is completely " +
        "filled with water. It's running approximately " +
        "horizontal between the east and west, though you " +
        "can't see very much besides that.\n\n");

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    add_prop(OBJ_S_WIZINFO,
        "This room is meant as a temporary room that Firestorm " +
        "moves to when leaving his grotto beneath Castle " +
        "Chimera. Player's aren't supposed to be here, but " +
        "if they do manage to get here somehow, they can only " +
        "go east, which is into Firestorm's grotto.\n");

    add_exit(GROTTO + "grotto", "east", "@@grotto_msg");
    add_exit(SPECIAL + "air_temp", "west", "@@west_block");
}

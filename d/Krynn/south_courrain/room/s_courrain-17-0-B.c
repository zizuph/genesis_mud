#include "../local.h"
#include CLOCKH
inherit S_COURRAIN + "s_courrain-B";
// inherit ROOM_BASE;

#define BLOODSEA_LINK "/d/Ansalon/goodlund/bloodsea/room/8b"

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the high seas are highly " +
        "rough, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "open waters of the high seas!\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    reset_sea_room();

    add_row_exit(BLOODSEA_LINK, "north", 0, 1);

}


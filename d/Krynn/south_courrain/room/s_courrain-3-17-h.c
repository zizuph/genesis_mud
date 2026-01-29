#include "../local.h"
#include CLOCKH
inherit S_COURRAIN + "s_courrain-h";

#define PB_LINK "/d/Ansalon/balifor/port_balifor/room/pier01"

public void
create_sea_room()
{
    set_special_short("Southwest of Port Balifor");

    ::create_sea_room();

    set_short("southwest of Port Balifor");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The turbulent waters of the Bay of Balifor here are " +
        "rough, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "waters of the Bay of Balifor.\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    reset_sea_room();

    add_row_exit(PB_LINK, "northeast", 0, 1);

}

#include "../local.h"
#include CLOCKH
inherit S_COURRAIN + "s_courrain-c";

#define FLOTSAM_LINK "/d/Ansalon/goodlund/bloodsea/room/flotsam/2e"

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The turbulent waters of the Blood Sea here are " +
        "rough, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "waters of the Blood Sea.\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    reset_sea_room();

    add_row_exit(FLOTSAM_LINK, "northwest", 0, 1);

}

int
no_sail()
{
    write("To your east is the reef known as The Black. Without a map " +
        "it would be suicide to try and navigate through it.\n");
    return 1;
}
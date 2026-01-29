#include "../local.h"
#include CLOCKH
inherit S_COURRAIN + "s_courrain-p";

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

    add_item(({"reef","the black"}),
       "To exit the passage known as the Eye of the Bull you would need " +
       "to navigate a dangerous reef known as The Black. Without a map, " +
       "it would be suicide to attempt it.\n");

    reset_sea_room();

    add_row_exit("xxx", "east", "@@no_sail", 1);

}

int
no_sail()
{
    write("To your east is the reef known as The Black. Without a map " +
        "it would be suicide to try and navigate through it.\n");
    return 1;
}
#include "../local.h"
#include CLOCKH
inherit S_COURRAIN + "s_courrain-i";

#define SILVANESTI_LINK "/d/Ansalon/silvanesti/new_kurinost/rooms/sandy_beach2"

public void
create_sea_room()
{
    set_special_short("The coastline of Silvanesti, near a narrow beach");

    ::create_sea_room();

    set_short("the coastline of Silvanesti, near a narrow beach");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item(({"beach","narrow beach","small beach","cliffs","cove",
        "sheltered cove","treacherous reefs","reefs","reef"}),
        "To your southwest the coastline of cliffs open into a very " +
        "narrow beach, a small sheltered cove protected by treacherous " +
        "reefs.\nOnly the most skilled of sailors would be able to " +
        "navigate their way through the reef to the cove though.\n");  

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The turbulent waters of the Courrain Ocean here are " +
        "rough, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "waters of the Courrain Ocean.\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    reset_sea_room();

    add_row_exit(SILVANESTI_LINK, "southwest", 0, 1);

}

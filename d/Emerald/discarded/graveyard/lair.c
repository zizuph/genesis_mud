inherit "/std/room";
inherit "/d/Emerald/common/guild/vamp/lib/lair";

#include <stdproperties.h>

public void
create_room()
{
    set_short("Dome room");
    set_long("   The green-marble walls of the room encircle you, reaching " +
        "high up to the domed ceiling, which is painted with a dark but " +
        "striking fresco.\n" +
        "   The circular room is quite spacious and completely barren " +
        "except for several coffins recessed in the eight shallow " +
        "alcoves which are set into the wall, spaced equidistantly.\n");

    add_item(({ "green wall", "green walls", "green marble wall",
                "green marble walls", "marble wall", "marble walls",
                "marble", "green marble", }),
        "The walls are formed from a deep-green, polished marble.\n");

    add_item(({ "ceiling", "domed ceiling", "fresco", }),
        "The ceiling is painted with a fresco which simply pictures a " +
        "a gathering of thick, dark, swirling clouds.  As you continue " +
        "to look at the fresco, it almost seems as if there is no dome" +
        "at all--that the murky, whorling clouds themselves form the " +
        "ceiling.\n");
        
    add_item(({ "alcove", "alcoves" }),
        "There are eight shallow alcoves spaced equidistantly around " +
        "the room.\n");

    remove_prop(ROOM_I_LIGHT);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop("_room_i_free_vamp_dvis", 1);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("under_church04", "east");

    add_coffins();
}

void
init()
{
    ::init();
    init_lair();
}

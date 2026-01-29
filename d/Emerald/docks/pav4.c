#include "defs.h"

inherit PAV_PATH_ROOM;

public string
pav_path_long()
{
    string long = ::pav_path_long();
    if (strlen(long))
    {
        long += "  ";
    }

    return long + "Just off the path to the east stands a small, windowless, " +
        "stone building.\n";
}

void
create_pavpath_room()
{
    add_exit("pav8", "north");
    add_door_exit(DOCK_DOOR_OBJ, "dock05", "south");
    add_door_exit(DOCK_DIR + "obj/bank_door", "bank", "east");

    add_item(({ "building", "small building", "small windowless building",
        "small windowless stone building", "small stone building",
        "stone building", "bank", "deposit", "vault" }),
        "One of the few proper buildings on the island, the small, one " +
        "story structure appears to be extremely secure, nonetheless.  A " +
        "sign above the massive door reads, \"Gnomes of Genesis\".\n");
    add_item(({ "sign", "sign above door", "sign above massive door",
        "sign above massive iron door", }),
        "The sign above the small stone building's door reads \"Gnomes of " +
        "Genesis\".\n");
}

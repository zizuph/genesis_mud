#include "defs.h"

inherit DOCK_ROOM;

void
create_pavpath_room()
{
}

public string
pav_path_long()
{
    return "A short path leads slightly uphill from the " +
        "docking area toward a large pavilion at the island's " +
        "center.  All around, you can hear the shouts of sea " +
        "captains intermingled with the sound of crashing waves " +
        "and screeching seagulls.";
}

nomask void
create_dock_room()
{
    set_em_long(pav_path_long() + "\n");
    remove_item("path");
    add_item(({ "path", "pathway" }),
        "The a short pathway leads between the pavilion at the " +
        "center of the island and the docking area, where circular " +
        "path provides access to each of the docks.\n");

    create_pavpath_room();
}

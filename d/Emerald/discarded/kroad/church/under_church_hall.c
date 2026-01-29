#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>

public void
create_hall()
{
}

nomask void
create_vamp_room()
{
    set_short("Narrow hallway");
    set_long("  A narrow hallway runs between two chambers " +
        "to the east and west.  Along the length of the hallway, " +
        "a series of archways on both sides have been bricked up.\n");

    add_item("chambers", "To the east, you can make out a small, " +
        "plain chamber with a statue in it.  At the end of the " +
        "hallway to the east, a short flight of stairs leads to " +
        "a large, dark chamber.\n");
 
    add_item(({ "stairs", "flight of stairs", "short flight of stairs", }),
        "The short flight of stairs leads down to a large, dark chamber " +
        "at the west end of the hallway.\n");

    add_item("hallway",
        "The narrow hallway runs between two chambers " +
        "to the east and west.  Along the length of the hallway, " +
        "a series of archways on both sides have been bricked up.\n");

    add_item("archways", "A series of six, opposing archways along " +
        "the length of the hallway have been bricked up.\n");

    create_hall();
}

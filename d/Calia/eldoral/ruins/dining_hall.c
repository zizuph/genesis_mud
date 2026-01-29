#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("In a long hall within the ruins of " +
        CASTLE_NAME);
    set_long("You are in a long hall that runs from " +
        "the north to the south. Above your head, " +
        "a high, vaulted ceiling coming from the " +
        "north ends abruptly at a lowered, flat " +
        "ceiling about half the height of the vaulted " +
        "one. The walls are unadorned, though they " +
        "bear the cracks and dust of decay. Long " +
        "slit-like windows in the east wall allow " +
        "thin beams of light to filter into the " +
        "room. In the " +
        "center of the room, a long heap of dried out " +
        "wood lies, slowly transforming into dust.\n\n");

    add_item(({"ceiling", "roof"}),
        "The once-grand vaulted ceiling now sports a large " +
        "number of holes where stones have fallen away, " +
        "exposing the mist-shrouded sky beyond.\n");
    add_item(({"walls"}),
        "The walls are made of simple stone blocks, with " +
        "long slits on the east wall allowing light " +
        "to stream down into the room.\n");
    add_item(({"floor", "ground"}),
        "The floor is quite elegantly paved with small " +
        "flagstones lain in intricate swirls and spirals.\n");
    add_item(({"slits", "windows"}),
        "High on the east wall, long slits serve as " +
        "windows, allowing light to enter the room. " +
        "Every now and then, a wisp of mist will slip " +
        "through, driven by the wind, only to vanish " +
        "again.\n");
    add_item(({"heap", "wood", "table"}),
        "The heap of wood chunks is long and rectangular " +
        "in shape, all that remains of a long table that "+
        "once dominated this room.\n");

    INSIDE;

    add_exit(RUIN + "main_hall_4", "north");
    add_exit(RUIN + "main_hall_5", "south");
}


#include "../defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    set_short("Outside the KoT Guildhall");
    set_em_long("Standing just inside the south gate of the Royal " +
        "Circle, the halls of the Keepers of Telberin surround you " +
        "to the north, east, and west.  Behind them, the royal palace " +
        "and the Temple of Telan-Ri loom over the rest of the edifices " +
        "in the circle, dominating the view to the north.  Out past the " +
        "gates, you can see the great South Avenue leading through the " +
        "southern parts of Telberin.\n");

    add_item("east",
        "A wide path leads east into the training hall of the Keepers " +
        "of Telberin.\n");

    add_item("west",
        "A wide path leads west into the recruitment office of the " +
        "Keepers of Telberin.\n");

    add_item("north",
        "A wide path leads north into the main hall of the Keepers of " +
        "Telberin.\n");

    add_exit("main_hall", "north");
    add_exit("training_hall1", "east");
    add_exit("recruitment_office", "west");
    add_exit("../tel10_07", "south");
}

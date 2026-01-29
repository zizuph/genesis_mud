#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    set_short("Western gate of Telberin");
    set_em_long("Just inside the western gate of Telberin, the wide west " +
        "avenue of the city separates the scientific quarter to the north " +
        "and the mercantile quarter to the south, leading east through two " +
        "of Telberin's famous gardens and into the grand Royal Circle and " +
        "and ending at the gates of the royal palace itself.  The great " +
        "Ri Circle runs north and south, providing access to the city's " +
        "business sections.\n");

    add_exit("tel03_10", "west");
    add_exit("tel05_10", "east");
    add_exit("tel04_11", "north");
    add_exit("tel04_09", "south");
}

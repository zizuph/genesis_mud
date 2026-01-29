#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    set_short("West avenue of Telberin, outside the royal palace");
    set_em_long("The great west avenue of Telberin begins here at the " +
        "Royal Circle, just beyond the magnificent gates of the royal " +
        "palace, extending out into the mercantile and scientific " +
        "quarters of the city.\n");

    add_exit("tel07_09", "south");
    add_exit("tel07_11", "north");
    add_exit("tel06_10", "west");
}

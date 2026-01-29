#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    set_short("West avenue of Telberin");
    set_em_long("Here the west avenue of Telberin passes between two " +
        "of the city's famous gardens on its way between the the west " +
        "gate and the gates of the royal palace.\n");

    add_exit("tel05_10", "west");
    add_exit("tel07_10", "east");
}

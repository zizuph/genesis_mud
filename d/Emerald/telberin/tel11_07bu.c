#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{

    set_em_long("The Royal Circle.\n");


    add_exit("tel12_08", "northeast");
    add_exit("tel10_07", "west");
    add_door_exit(TELBERIN_MAGIC_GARDEN_DIR + "garden_gate",
        TELBERIN_MAGIC_GARDEN_DIR + "magic1", "east");

}
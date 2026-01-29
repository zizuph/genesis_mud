#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit "/d/Krynn/std/room";

void
create_room()
{
    set_short("South alcove on the main level");
    set_long("You are standing on a landing in a small alcove." +
        " A spiral staircase carved out of the natural rock" +
        " winds around the mountain going both up and down." +
        " Several arched doorways lead further into the" +
        " mountain.\n");
        

    INSIDE;
    LIGHT;

    add_item(({"tunnel","tunnels"}), "Hewn out of the" +
        " solid rock, this tunnel extends a long way" +
        " into the mountain. Every few feet an ornate" +
        " sconce holds a flickering torch which serves" +
        " as the only source of light in the tunnel.\n");

    add_exit(NDIR + "02_inn/a_2_s", "up", 0);
    add_exit(NDIR + "00_caves/a_0_n", "down", 0);
    add_exit(NDIR + "01_main/fling_open", "left", 0);
    add_exit(NDIR + "01_main/r_1_s", "right", 0);
    add_exit(NDIR + "01_main/a_1_e", "forward", 0);
    add_exit(NDIR + "01_main/a_1_w", "backward", 0);


    reset_room();
}


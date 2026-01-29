inherit "/d/Krynn/sancrist/nevermind/cave.c";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>

void
create_cave_room()
{
    set_short("North alcove on the main level");
    set_long("You are standing on a landing in a small alcove." +
      " A spiral staircase carved out of the natural rock" +
      " winds around the mountain going both up and down." +
      " Several arched doorways lead further into the" +
      " mountain.\n");

    add_item(({"tunnel","tunnels"}), "Hewn out of the" +
      " solid rock, this tunnel extends a long way" +
      " into the mountain. Every few feet an ornate" +
      " sconce holds a flickering torch which serves" +
      " as the only source of light in the tunnel.\n");

    add_exit(N_02 + "a_2_w", "up", 0);
    add_exit(N_00 + "a_0_e", "down", 0);
    add_exit(N_01 + "a_1_n_w", "west", 0);
    add_exit(N_01 + "a_1_n_e", "east", 0);
    add_exit(N_01 + "r_1_n", "north", 0);
    add_exit(N_01 + "fling_open", "south", 0);


    reset_room();
}


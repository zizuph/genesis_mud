/*  /d/Faerun/sea/whalebones/rooms/beach1.c
*
*   By Nucifera, 2020
*
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_WHALEB_OUTDOOR;


void
create_whaleb_outdoor()
{
    extraline = "There is a gentle crunch underfoot "
        +"crunch underfoot of shells and the remains of various sea life"
        +". Columns of skeletal substance from large seaborne vertebrate "
        +"have scattered themselves along the entire length of coast "
        +"around you. Driftwood in all hues and states of decomposition"
        +" have dispersed on the gray-tinged ";

  set_short("Somewhere on a narrow bone littered beach");

    add_std_herbs("mere");


    add_item(({"path", "footsteps"}), "There is not a footstep in sight o"
        +"n this sandy wasteland but your own.");

    add_item(({"floor", "ground"}),
        "Your immered to the ankle in sand, pebbles, and other debris dep"
        +"osited by the ebbing water. A You notice weathered bone fragmen"
        +"ts by your feet.\n");

    add_room_tell("The stomach-churning aroma of rotting sea life drifts "
        +"past you. ");

    set_no_exit_msg( ({"northwest", "west", "southwest"}), "There is a cl"
      +"iff in the way. You decided it is too risky to climb a horizontal"
      +" face of rock.\n");

    set_no_exit_msg( ({"north"}), "You consider moving further north, but"
      +"noticing the crumbling rockface above, decide against it.\n");

    set_no_exit_msg( ({"east", "southeast"}), "Breaking waves deter you fr"
      +"om moving in that direction.\n");

    add_exit(ROOM_DIR + "beach2.c", "south");
}

void
reset_faerun_room()
{
    set_searched(0);
}

// hall7.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_hall.c";
#include "../local.h"

object guard1, guard2;

reset_spur_room()
{
    if (!guard1)
	(guard1 = clone_object(SNPC + "guard"))->move(TO);
    if (!guard2)
	(guard2 = clone_object(SNPC + "guard"))->move(TO);
}

void
create_spur_room()
{
    AE(ROOM + "east_gap", "southeast", 0);
    clone_object(SOBJ + "steeldooro2")->move(TO);    

    make_the_room("To the southeast, the tunnel becomes a " +
      "wide corridor running from east to west.");

    add_prop("_room_i_allow_steed", 1);
    reset_spur_room();
}



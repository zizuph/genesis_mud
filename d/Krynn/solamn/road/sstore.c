/* Aridor, 04/99 */

#include <local.h>

inherit ROOM_BASE

object door;

void
create_road_room()
{
    set_short("Down by the riverside of the Vingaard River");
    set_long("You are down by the side of the Vingaard River, standing at the " +
	     "edge of the river directly below the cliff. The water of the river " +
	     "is currently low, allowing you to cross.\n");
    add_exit("/d/Krynn/solamn/eplains/ferryman_hut","southeast");
    reset();
}

void
reset_road_room()
{
    if (!door)
      (door = clone_object(DOOROUTSIDE))->move(TO);
}

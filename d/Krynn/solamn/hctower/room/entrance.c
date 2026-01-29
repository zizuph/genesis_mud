/* created by Aridor 06/21/93 */

inherit "/std/room";

#include "../local.h"
#define VKEEPGUARD "/d/Krynn/solamn/hctower/spur/npc/guard"

object guard1, guard2;


create_room()
{
    set_short("Outside the entrance to the High Clerist Tower");
    set_long(BS("You are just outside the huge steel gates leading "
	+   "into the High Clerist Tower. Towards your southeast "
	+   "the Plains of Solamnia stretch out to the horizon. "
	+   "The Vingaard Mountains extend to the northeast and south, "
	+   "with the tower guarding the entrance to a valley.",SL));

    OUTSIDE;

    add_exit(SPLAINS,"southeast",0);
    clone_object(OBJ + "steeldooro")->move(TO);

    add_item(({"tower","fortress"}),BS("You look up to the tower but you "
	+   "can barely make out its top. The base of the tower is really "
	+   "a solid fortress, like a silent guardian watching its "
	+   "surroundings.",SL));
    add_item("plains",BS("These plains are vast! You cannot see anything "
	+   "else but plains all the way to the east and south. It seems "
	+   "that brownish grass grows everywhere, making patterns as the "
	+   "wind touches it.",SL));
    add_item("mountains",BS("The mountains look really fierce. No wonder was "
	+   "it possible to build a fortress here to guard the only passway "
	+   "across the mountains.",SL));

    reset_room();
}


reset_room()
{
    if (!guard1)
	(guard1 = clone_object(VKEEPGUARD))->move_living(0,this_object());
    if (!guard2)
	(guard2 = clone_object(VKEEPGUARD))->move_living(0,this_object());
}

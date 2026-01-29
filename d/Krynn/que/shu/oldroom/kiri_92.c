
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. Scattered around you are the"
      + " tents and huts of the Que Kiri people. Looking in one tent"
      + " you can make out a sleeping boy on a fur bed with a"
      + " dog curled up at his feet. The dog gives you a full looking"
      + " over, deciding that your not intending to distrub his"
      + " master's sleep, and drifts back to sleep.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_81","northwest");
    add_exit(ROOM + "kiri_a3","southeast");

}

int
hook_change_room(int which)
{
    if (which == 0)
      {
	  if (monster)
	    return 0;
	  monster = RANDOM_MEET(TABLE);
	  monster->move_living("xx",TO);
	  return 1;
      }
    if (which == 1)
      if (monster)
	return 0;
    return 1;
}


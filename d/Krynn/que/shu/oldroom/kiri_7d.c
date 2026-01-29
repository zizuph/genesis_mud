
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. Towards the north"
      + " you can make out some strange wooden structures"
      + " that appear to have smoke rising out of the center"
      + " of them. Looking south, you notice the all to familar"
      + " tents that seem to make up the general living quarters"
      + " of the Que Kiri people.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_6d","north");
    add_exit(ROOM + "kiri_8d","south");

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


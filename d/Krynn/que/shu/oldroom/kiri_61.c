
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
      + " tents and huts of the Que Kiri people. Small children run"
      + " here and there playing games, while their mothers are busy"
      + " working on chores of daily life. The young men all seem"
      + " to be gone, probably out on a hunting expedition.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_71","south");
    add_exit(ROOM + "kiri_52","northeast");

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


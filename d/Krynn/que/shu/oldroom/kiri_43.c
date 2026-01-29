
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. The tents and huts begin"
      + " to thin out here. The people living in these huts seem"
      + " older and more elderly then the other families. Perhaps"
      + " the privilage of their age allow them to live in a less"
      + " crowded area of the village.	There is another path here"
      + " that branches off of the one your on and heads back towards"
      + " the center of the village.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_34","northeast");
    add_exit(ROOM + "kiri_54","southeast");
    add_exit(ROOM + "kiri_52","southwest");

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


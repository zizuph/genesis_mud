
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("This path leads southwest, off into the center of the"
     + " village. While to the northeast you can spot some villagers"
     + " crowding around a stone building.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_4b","northeast");
    add_exit(ROOM + "kiri_69","southwest");

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


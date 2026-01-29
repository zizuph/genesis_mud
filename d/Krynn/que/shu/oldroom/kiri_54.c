
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("This path leads southeast, off into the center of the"
     + " village. While to the northwest you can spot a few"
     + " widely spaced cloth tents.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_43","northwest");
    add_exit(ROOM + "kiri_65","southeast");

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


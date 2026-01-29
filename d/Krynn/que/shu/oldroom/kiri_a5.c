
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("This path leads northeast, off into the center of the"
     + " village. While to the southwest it will take you to the"
     + " jumble of tents where most of the Que Kiri live. As you"
     + " stand here deciding which way to go, a large flock of birds"
     + " suddenly come flying over the village walls heading due"
     + " southwest. How very strange!", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_96","northeast");
    add_exit(ROOM + "kiri_b4","southwest");

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


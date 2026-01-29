
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Shaman's hut");
    set_long(BS("You stand inside a very dusty hut, that doesn't"
      + " look as if its seen much use lately. Looking around you"
      + " notice alot of religious artifacts, herbal pouches,"
      + " and colorful robes thrown here and there. Dust covers"
      + " everything though, you wonder what happened to the"
      + " hut's owner. As you start to leave you accidently step"
      + " on something laying on the ground, it looks to be a"
      + " book.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_69","out");

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


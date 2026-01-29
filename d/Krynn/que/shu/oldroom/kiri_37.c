
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"
#define TABLE "/d/Krynn/common/rndtables/tblwar"

object monster;

void
create_attack_room()
{
    set_short("Temple of the Ancestors");
    set_long(BS("You stand before a lifesize stone statue of"
      + " what appears to be a Que Kiri warrior. Your gaze wanders"
      + " out through the columns noticing a brightly colored building"
      + " to the north. Glancing up and out over the village wall you"
      + " can't be sure, but there seems to be something up in the sky."
      + " Its to far away though...and now you lost it..must have been"
      + " your imagination.", 70)); 
  set_change_long(1,BS(BURN_MACH+"There is a pile of rubble that "
    + "stands here. There are a pair of stone carved legs sticking "
    + "from the pile of rubble. "+BURN_SCREAMA+BURN_SHAPESH,70));

    OUTSIDE;

    add_exit(ROOM + "kiri_47","south");

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


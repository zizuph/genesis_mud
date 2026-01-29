
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Village well");
    set_long(BS("The activity here is tremendous! Villagers of every"
      + " age, child to adult, stand in lines around a great well"
      + " waiting to get water. Four large wooden tripods are placed"
      + " around the well, used to lower and raise leather lined baskets"
      + " which bring up water from some underground reservoir. You"
      + " wonder what would happen to this village if the well were"
      + " to dry up. The result would probably mean the end of the"
      + " village itself.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_65","northeast");

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


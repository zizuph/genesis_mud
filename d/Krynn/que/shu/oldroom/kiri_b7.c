
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a gravel path in Que Kiri");
    set_long(BS("Looking around you estimate that the village"
      + " is some 500 meters across. Consisting mainly of large stone"
      + " buildings near the center with less permanent tent structures"
      + " on the outer edges.	You've heard these people referred"
      + " to as barbarians back home, but nothing here points to the savage"
      + " group of people that you expected. Rather, you see kindness"
      + " and goodness radiating from these people in the way they"
      + " greet you and smile.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_a7","north");
    add_exit(ROOM + "kiri_c7","south");

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


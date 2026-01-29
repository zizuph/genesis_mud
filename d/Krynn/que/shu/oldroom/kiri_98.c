
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On grass path in Que Kiri");
    set_long(BS("The path weeds its way through some stone structures"
      + " heading northwest towards the center of the village, and"
      + " also to the southeast where you can spot some tents and" 
      + " huts.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_87","northwest");
    add_exit(ROOM + "kiri_a9","southeast");

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

